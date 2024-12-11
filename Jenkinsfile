pipeline {
    agent any

    stages {
        stage('Checkout') {
            steps {
                 git url: 'https://github.com/ppvictoriaaa/SP_kursova_lab4.git', credentialsId: 'jenkins'
            }
        }
        
        stage('Build') {
            steps {
                bat '"C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\MSBuild\\Current\\Bin\\MSBuild.exe" test_repos.sln /t:Build /p:Configuration=Debug'
            }
        }

        stage('Test') {
            steps {
                bat "x64\\Debug\\test_repos.exe --gtest_output=xml:test_report.xml"
            }
        }
    }

    post {
    always {
        // Publish test results using the junit step
        // Specify the path to the XML test result files
        junit('test_report.xml')

    }
}
}