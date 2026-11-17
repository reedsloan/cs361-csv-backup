SPRINT 2: MICROSERVICE 1 CSV BACKUP
11/16/26

The goal for Sprint 2 is to back up a CSV file, keep earlier copies, and report an error if the file is missing. backup.cpp handles the file copy and gives each backup its own name. server.cpp will receive the CSV path over HTTP and return either the backup path or an error. test_client.cpp will check that repeated requests preserve earlier backups and that the service can still handle a valid request after a failed one.