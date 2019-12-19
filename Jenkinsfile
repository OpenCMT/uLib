pipeline {

    agent {
        docker {
            image 'infnpd/cmt-environment:1.1-centos7'
            args '-u 0:0'
            label 'DOCKER'
        }
    }

    environment {
        NEXUS_PD_CREDS = credentials('jenkins-nexus-pd-creds')
        NEXUS_PD_URL = 'https://cld-smact-02.pd.infn.it/artifacts/repository/muotom/devel/centos7/x86_64/'
    }

    stages {

        stage('Build') {

            steps {
                sh "mkdir build && cd build && cmake -DNODOXYGEN=ON .. && make rpm"
            }

        }
        stage('Deploy') {

            steps {
                sh "find . -name '*.x86_64.rpm' curl -v -k --user '${NEXUS_PD_CREDS_USR}:${NEXUS_PD_CREDS_PSW}' --upload-file '{}' ${NEXUS_PD_URL} ';'"
            }

        }

    }

}
