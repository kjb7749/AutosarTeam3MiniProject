pipeline {
  agent any
  stages {
    stage('fetch') {
      steps {
        git(url: 'https://github.com/kjb7749/AutosarTeam3MiniProject.git', branch: 'master', poll: true)
      }
    }

    stage('build') {
      steps {
        sh 'dir'
      }
    }

  }
}