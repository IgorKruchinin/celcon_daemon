# celcon_daemon
## Описание
ЦЕЛКОН (celcon) - система контроля целостности на основе проверки контрольных сумм файлов из списка отслеживаемых файлов
## Основные функции
- Добавление, изменение и удаление записей в списке отслеживаемых файлов
- Слежение за событиями файлов посредством inotify
- Вычисление контрольных сумм по выбранному пользователем алгоритму в случае возникновения события inotify
- Взаимодействие с пользователем: отправка уведомлений об изменении файлов пользователям, получение данных и команд от пользователя, оповещение пользователя о внештатных ситуациях возникших при отслеживании файлов
## Разделение ролей пользователей
- Наблюдатель (Viewer) - может просматривать список отслеживаемых файлов и их статусы, а также статистику изменений во времени без возможности вносить изменения в список отслеживания и влиять на других пользователей
- Редактор (Editor) - все привелегии Наблюдателя и возможность изменения списка отслеживаемых файлов без возможности влиять на других пользователей
- Администратор (Administrator) - все привелегии Редактора и возможность добавлять, изменять и удалять пользователей и их данные
## Взаимодействие с пользователем
Взаимодействие с пользователем производится посредством сокетов TLS и отправки сообщений в синтаксисе JSON
### Типы сообщений
- Событие (evt) - отправка пользователю сообщений о наступившем событии (например, изменении файлов)
- Команда (cmd) - получение от пользователя команд и сопутствующих данных (например, внесение файла в список отслеживания)
- Ответ на команду (answ) - отправка пользователю ответа на поступившую команду с кодом ответа, текстом сообщения и сопутствующими данными
## Диаграмма базы данных:
```mermaid
erDiagram
    roles ||--o{ users : "назначается"
    posts ||--o{ users : "занимает"
    users ||--o{ tracking_files : "отслеживает"
    users ||--o{ login_history : "входит"
    hash_algorithms ||--o{ tracking_files : "используется"
    tracking_files ||--o{ changes_history : "имеет"

    roles {
        INTEGER role_id PK "AUTO_INCREMENT"
        VARCHAR role_name
    }

    posts {
        INTEGER post_id PK "AUTO_INCREMENT"
        VARCHAR post_name
    }

    users {
        INTEGER user_id PK "AUTO_INCREMENT"
        VARCHAR user_login
        INTEGER role_id FK
        VARCHAR name
        VARCHAR surname
        VARCHAR patronymic
        INTEGER post_id FK
    }

    hash_algorithms {
        INTEGER algorithm_id PK "AUTO_INCREMENT"
        VARCHAR algorithm_name
    }

    tracking_files {
        INTEGER file_id PK "AUTO_INCREMENT"
        VARCHAR file_path "NOT NULL"
        INTEGER user_id FK
        INTEGER algorithm_id FK
        VARCHAR file_hash
        TIMESTAMP hash_actual_time
    }

    changes_history {
        INTEGER change_id PK "AUTO_INCREMENT"
        INTEGER file_id FK
        VARCHAR new_hash
        TIMESTAMP change_time
    }

    login_history {
        INTEGER login_id PK "AUTO_INCREMENT"
        INTEGER user_id FK
        TIMESTAMP login_time
    }

    system_log_messages {
        INTEGER log_id PK "AUTO_INCREMENT"
        TEXT log_message
        TIMESTAMP log_time
    }
```
