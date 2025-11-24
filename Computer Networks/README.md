# Computer Networks

네트워크 기본 개념과 실습 자료를 정리하는 폴더입니다. OSI 모델, TCP/IP, 라우팅, 스위칭, 소켓 프로그래밍, HTTP 등 실무와 학습에 필요한 내용을 포함하세요.

권장 항목

- OSI 7계층 및 각 계층 역할
- TCP vs UDP 차이와 핸드셰이크
- 소켓 프로그래밍 예제 (C/Python)
- 네트워크 도구 사용법 (ping, traceroute, netstat)

간단 예시: Python으로 TCP 서버 실행

```powershell
python -c "import socket; s=socket.socket(); s.bind(('0.0.0.0',9000)); s.listen(1); print('listening');"
```

