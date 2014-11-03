#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "templates.h"


LtkList ltk_list_new()
{
  LtkList list = malloc(sizeof(struct _template_list));
  list->size = 0;
  list->start = NULL;
  list->end = NULL;
  return list;
}

void ltk_list_nodepush(LtkList list,LtkListNode node)
{
  if(list == NULL) return;
  node->next = list->start;
  list->start = node;
  if(list->end == NULL) list->end = node;
  list->size++;
}

LtkListNode ltk_list_get_start(LtkList list)
{
  if (list==NULL || list->start==NULL) return NULL;
  return list->start;
}

LtkListNode ltk_list_get_end(LtkList list)
{
  if (list==NULL || list->end==NULL) return NULL;
  return list->end;
}

void ltk_list_remove(LtkList list,LtkListNode node)
{
  if (list == NULL || list->start==NULL) return;
  struct _template_list_node *node_tofree,*prev;
  node_tofree=list->start;
  while (node_tofree != node) {
    if(node_tofree->next == NULL) return;
    prev = node_tofree;
    node_tofree = node_tofree->next;
  }
  if(node_tofree == list->start) list->start = node_tofree->next;
  else prev->next = node_tofree->next;
  free(node_tofree);
}

void ltk_list_pop_start(LtkList list)
{
  if (list==NULL || list->start==NULL) return;
  struct _template_list_node *nodetofree;
  nodetofree=list->start;
  list->start = list->start->next;
  free(nodetofree);
}

void ltk_list_pop_end(LtkList list)
{
  if (list==NULL || list->end==NULL) return;
  struct _template_list_node *iter;
  iter=list->start;
  if(iter==list->end) {
    free(iter);
    list->start = list->end = NULL;
  }
  else { 
    while(iter->next!=list->end) iter=iter->next;
    free(iter->next);
    iter->next = NULL;
    list->end = iter;
  }
  list->size--;
}

int ltk_list_get_size(LtkList list)
{
  if(list==NULL) return 0;
  return list->size;
}


LtkListIterator ltk_list_iterator_new(LtkList list)
{
  if(list==NULL || list->start == NULL) return NULL;
  return (LtkListIterator)list->start;
}


