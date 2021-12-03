# twitch-chat-crawler

트위치 채팅 분석을 위한 채팅 수집기
---
## TODO
- [ ] DB 연결 (라이브러리 알아보기)
- [ ] 채널 데이터 파싱 후 DB에 저장
- [ ] 채널을 추가 할 수 있는 API 추가 (socket server 구현)
---
## BUILD
```
$ docker build . -t crawler
```
---
## RUN
```
$ docker exec --privileged -it crawler sh
```