//#include <linux/config.h>
#include <linux/version.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/slab.h>
#include <linux/vmalloc.h>
#include <linux/mm.h>
#include <linux/ioctl.h>
#ifdef MODVERSIONS
#  include <linux/modversions.h>
#endif
#include <asm/io.h>
#include <asm/system.h>
#include <asm/uaccess.h>



/* methods of the character device */
static int ltkb_open(struct inode *inode, struct file *filp);
static int ltkb_release(struct inode *inode, struct file *filp);
static int ltkb_mmap(struct file *filp, struct vm_area_struct *vma);
static ssize_t ltkb_read(struct file *filp,
			 char __user *buffer,
			 size_t count,
			 loff_t *offp);
static ssize_t ltkb_write(struct file *filp,
			  const char __user *buffer,
			  size_t count,
			  loff_t *offp);


// internal data
// length of the two memory areas
#define NPAGES 16
// pointer to the vmalloc'd area - alway page aligned
static int *vmalloc_area;
// pointer to the kmalloc'd area, rounded up to a page boundary
static int *kmalloc_area;
// original pointer for kmalloc'd area as returned by kmalloc
static void *kmalloc_ptr;


#define BUF_LEN 80
static int Device_Open = 0;

static char Message[BUF_LEN];
/*
 * How far did the process reading the message get?
 * Useful if the message is larger than the size of the
 * buffer we get to fill in device_read.
 */
static char *Message_Ptr;


struct ltkb_dev {
  struct cdev cdev;              // device structure
  struct semaphore semaphore;    // lock semaphore for race control
  char *message;                 // message passing from/to user
  unsigned int size;             // size of data stored
  unsigned int acl_key;          // user access control
};

struct ltkb_dev *_ltkb_devices;   // devices array //





/////// OPEN AND RELEASE ///////////////////////////////////////////////////////
static int ltkb_open(struct inode *inode, struct file *filp)
{
  // insert cdev data in dev structure and file->private_data //
  struct ltkb_dev *dev;
  dev = container_of (inode->i_cdev, struct ltkb_dev, cdev);

  // this shares dev for all methods //
  filp->private_data = dev;

  pr_debug("ltk bridge opened");
  return 0;
}
/* character device last close method */
static int ltkb_release(struct inode *inode, struct file *filp)
{
  pr_debug("ltk bridge released");
  return 0;
}
// -------------------------------------------------------------------------- //



// kmalloc instancer //
int ltkb_kmem(struct file *filp, struct vm_area_struct *vma)
{
  int ret;
  long length = vma->vm_end - vma->vm_start;

  /* check length - do not allow larger mappings than the number of
     pages allocated */
  if (length > NPAGES * PAGE_SIZE)
    return -EIO;

  /* map the whole physically contiguous area in one piece */
  if ((ret = remap_pfn_range(vma,
			     vma->vm_start,
			     virt_to_phys((void *)kmalloc_area) >> PAGE_SHIFT,
			     length,
			     vma->vm_page_prot)) < 0) {
    return ret;
  }
  return 0;
}
// vmalloc instancer //
int ltkb_vmem(struct file *filp, struct vm_area_struct *vma)
{
  int ret;
  long length = vma->vm_end - vma->vm_start;
  unsigned long start = vma->vm_start;
  char *vmalloc_area_ptr = (char *)vmalloc_area;
  unsigned long pfn;

  /* check length - do not allow larger mappings than the number of
     pages allocated */
  if (length > NPAGES * PAGE_SIZE)
    return -EIO;

  /* loop over all pages, map it page individually */
  while (length > 0) {
    pfn = vmalloc_to_pfn(vmalloc_area_ptr);
    if ((ret = remap_pfn_range(vma, start, pfn, PAGE_SIZE,
			       PAGE_SHARED)) < 0) {
      return ret;
    }
    start += PAGE_SIZE;
    vmalloc_area_ptr += PAGE_SIZE;
    length -= PAGE_SIZE;
  }
  return 0;
}



// mmap function //
static int ltkb_mmap(struct file *filp, struct vm_area_struct *vma)
{
  /* at offset 0 we map the vmalloc'd area */
  if (vma->vm_pgoff == 0) {
    return ltkb_vmem(filp, vma);
  }
  /* at offset NPAGES we map the kmalloc'd area */
  if (vma->vm_pgoff == NPAGES) {
    return ltkb_kmem(filp, vma);
  }
  /* at any other offset we return an error */
  return -EIO;
}




////////////// CHAR DEVICE READ/WRITE  /////////////////////////////////////////
static ssize_t ltkb_read(struct file *filp,	/* see include/linux/fs.h   */
			 char __user *buffer,	/* buffer to fill with data */
			 size_t length,	/* length of the buffer     */
			 loff_t * offset)
{

#ifdef _DEBUG
  printk(KERN_INFO "device_read(%p,%s,%d)", filp, buffer, (int)length);
#endif
  
  return 0;
}

static ssize_t ltkb_write(struct file *filp,
			  const char __user *buffer,
			  size_t length,
			  loff_t * offset)
{
#ifdef _DEBUG
  printk(KERN_INFO "device_write(%p,%s,%d)", filp, buffer, (int)length);
#endif
  return 0;
}
// -------------------------------------------------------------------------  //


#define LTKB_IOC_HEADER 'b'

#define LTKB_IOC_RESET _IO(LTKB_IOC_HEADER, 0)
#define LTKB_IOC_PING  _IOWR(LTKB_IOC_HEADER, 1, char)

#define LTKB_IOC_MAXNR 1

////////////// IOCTL ///////////////////////////////////////////////////////////
int ltkb_ioctl(struct inode *inode, struct file *filp, 
	       unsigned int cmd, unsigned long arg)
{
  char c = 0;
  int retval = 0;

  /*
   * extract the type and number bitfields, and don't decode
   * wrong cmds: return ENOTTY (inappropriate ioctl) before access_ok()
   */
  if (_IOC_TYPE(cmd) != LTKB_IOC_HEADER) return -ENOTTY;
  if (_IOC_NR(cmd) > LTKB_IOC_MAXNR) return -ENOTTY;

  // TODO user access control //


  switch(cmd) {
  case LTKB_IOC_RESET:
    if(!capable(CAP_SYS_ADMIN))
      return -EPERM;
    // TODO free all memory mapping//
    break;
  case LTKB_IOC_PING:
    retval = __get_user(c,(char __user *)arg);
    c++;    
    retval = __put_user(c,(char __user *)arg);
    break;
  default:
    return -ENOTTY;
  }
  return retval;

}
// -------------------------------------------------------------------------  //





#ifndef LTKB_MAJOR
#define LTKB_MAJOR 0
#endif

#ifndef LTKB_NR_DEVS
#define LTKB_NR_DEVS 4
#endif

#ifndef LTKB_DEVICE_NAME
#define LTKB_DEVICE_NAME "ltkb"
#endif



/* the file operations, i.e. all character device methods */
static struct file_operations ltkb_fops = {
  .open = ltkb_open,
  .release = ltkb_release,
  .read = ltkb_read,
  .write = ltkb_write,
  .ioctl = ltkb_ioctl,
  .mmap = ltkb_mmap,
  .owner = THIS_MODULE,
};

static int _ltkb_major_number = LTKB_MAJOR;

// Module init function ////////////////////////////////////////////////////////
static int __init ltkb_init(void)
{
  int i,ret = 0;
  dev_t dev = 0;

  // REGISTER DEVICE //
  if(_ltkb_major_number)
    {
      dev = MKDEV(_ltkb_major_number,0);
      ret = register_chrdev_region(dev, LTKB_NR_DEVS, LTKB_DEVICE_NAME);
    }
  else {
    ret = alloc_chrdev_region(&dev, 0, LTKB_NR_DEVS, LTKB_DEVICE_NAME );
    _ltkb_major_number = MAJOR(dev);
  }
  if (ret < 0) {
    printk(KERN_WARNING "could not allocate major number %d for ltkb\n",
	   _ltkb_major_number);
    return ret;
  }

  // ALLOCATE DEVICES //
  _ltkb_devices = kmalloc( LTKB_NR_DEVS * sizeof(struct ltkb_dev), GFP_KERNEL );
  if(!_ltkb_devices) {
    printk(KERN_ERR "error allocating device structure in memory");
    return -ENOMEM;
  }
  memset(_ltkb_devices, 0, LTKB_NR_DEVS * sizeof(struct ltkb_dev));

  // SETUP DEVICES //
  for (i = 0 ; i < LTKB_NR_DEVS ; i++ )
    {
      struct ltkb_dev *dev = &_ltkb_devices[i];
      int devno = MKDEV(_ltkb_major_number, i);
      cdev_init (&dev->cdev, &ltkb_fops);
      dev->cdev.owner = THIS_MODULE;
      dev->cdev.ops = &ltkb_fops;
      ret = cdev_add(&dev->cdev,devno,1);
      if(ret) printk(KERN_NOTICE "Error %d adding ltkb%d device", ret, i);
      init_MUTEX(&dev->semaphore);
    }
  printk( KERN_NOTICE "ltk bridge module loaded");
  return ret;
}

// module release //
static void __exit ltkb_exit(void)
{
  // remove the character deivce //
  int i;
  dev_t devno = MKDEV(_ltkb_major_number,0);
  if(_ltkb_devices)
    {
      for(i=0;i<LTKB_NR_DEVS;i++)
	cdev_del(&_ltkb_devices[i].cdev);
      kfree(_ltkb_devices);
    }
  unregister_chrdev_region(devno,LTKB_NR_DEVS);
  printk( KERN_NOTICE "ltk bridge module unloaded");
}
//  ------------------------------------------------------------------------  //




//////////////////// Main Module Init ///////////////////
						       //
module_init(ltkb_init);                                //
module_exit(ltkb_exit);                                //
						       //
MODULE_DESCRIPTION("ltk bridge memory dispatcher");    //
MODULE_AUTHOR("andrea");                               //
MODULE_LICENSE("Not licenced yet");                    //
						       //
/////////////////////////////////////////////////////////
