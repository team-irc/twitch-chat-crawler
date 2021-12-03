## todo
- [ ] 계정 추가하기
- [ ] run 하는순간 바로 실행되도록 바꾸기

---

## build
```
$ docker build . -t db
```

## run
```
$ docker run -it db sh
```

## 발생한 에러

문제: mysqld 명령 실행 시 에러메세지 (Could not open mysql.plugin table: "Table 'mysql.plugin' doesn't exist". Some plugins may be not loaded)
원인: https://support.plesk.com/hc/en-us/articles/213914385-MySQL-MariaDB-fails-to-start-on-a-Plesk-for-Linux-server-Can-t-open-and-lock-privilege-tables
해결: skip-grant-tables를 설정 파일에 추가

증상: 컨테이너 빌드 후 mysqld 명령어 실행 시 에러
메세지: [ERROR] Can't open and lock privilege tables: Table 'mysql.servers' doesn't exist
원인: https://deeplify.dev/database/troubleshoot/can-not-open-and-lock-privilege-tables