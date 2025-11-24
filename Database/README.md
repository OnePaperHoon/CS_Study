# Database

데이터베이스 관련 개념과 실습 정리를 위한 폴더입니다. SQL 기본, 인덱스, 트랜잭션, 정규화 등의 이론과 간단한 실습 코드 및 쿼리를 정리해 둡니다.

권장 내용

- 기본 SQL 문법 (SELECT, INSERT, UPDATE, DELETE)
- 스키마 설계와 정규화
- 인덱스와 성능 최적화
- 트랜잭션과 격리 수준
- 샘플 데이터와 쿼리 예제

실습 환경

- 로컬에서 SQLite를 사용하면 별도 설치 없이 빠르게 실습 가능합니다.
- 또는 Docker로 MySQL/PostgreSQL 컨테이너를 띄워 실습할 수 있습니다.

예시: SQLite 사용

```powershell
sqlite3 sample.db
.schema
SELECT * FROM users;
```

