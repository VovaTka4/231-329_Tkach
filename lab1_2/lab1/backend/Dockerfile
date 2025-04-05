FROM python:3.11.11-slim-bullseye

ENV PYTHONDONTWRITEBYTECODE 1
ENV PYTHONUNBUFFERED 1

# каталог который будет корнем для копирования 
# файлов и для запуска команд внутри образа
WORKDIR /backend

COPY requirements.txt .
RUN pip install -r requirements.txt

# скопировать остальные файлы backend в "." (workdir)
COPY . .