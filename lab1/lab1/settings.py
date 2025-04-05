"""
КОНСПЕКТ

# Файл с настройками
# Настройки все и для всего
# Тут задаются константы, но всякое криптографическое(пароли логины и тд и тп) лучше вычищать из исходников, и добавлять
  во всякие .env файлы и заставлять питон подсаживать эти файлы на место строчек
# Константа = содержимое
# ХАБ чтобы собрать все константы вместе и фреймворковские и ваши личные!

"""

from pathlib import Path

# Build paths inside the project like this: BASE_DIR / 'subdir'.
BASE_DIR = Path(__file__).resolve().parent.parent


# Quick-start development settings - unsuitable for production
# See https://docs.djangoproject.com/en/5.1/howto/deployment/checklist/

# SECURITY WARNING: keep the secret key used in production secret!
SECRET_KEY = 'django-insecure-h23g&*0zf+(n2%g7m!6hsro$g!m%cnb%%p5q-l#a*et+r8ez+s'

# SECURITY WARNING: don't run with debug turned on in production!
DEBUG = False

ALLOWED_HOSTS = ['127.0.0.1'] # > СПИСОК ХОСТНЕЙМОВ ИЗ ЗАГОЛОВКОВ HTTP-ЗАПРОСОВ, КОТОРЫМ БЭКЕНД НЕ БУДЕТ ОТКАЗЫВАТЬ В ОБРАБОТКЕ
# В ОТВЕТ НА ЗАПРОСЫ ОТ ИНЫХ ХОСТНЕЙМОВ, БУДЕТ ВОЗВРАЩАТЬ КОД 400 ИЛИ ДРУГИЕ ОШИБКИ

# Application definition

INSTALLED_APPS = [
    'django.contrib.admin',
    'django.contrib.auth',
    'django.contrib.contenttypes',
    'django.contrib.sessions',
    'django.contrib.messages',
    'django.contrib.staticfiles',
    
    'mainapp'
]

MIDDLEWARE = [
    'django.middleware.security.SecurityMiddleware',
    'django.contrib.sessions.middleware.SessionMiddleware',
    'django.middleware.common.CommonMiddleware',
    'django.middleware.csrf.CsrfViewMiddleware',
    'django.contrib.auth.middleware.AuthenticationMiddleware',
    'django.contrib.messages.middleware.MessageMiddleware',
    'django.middleware.clickjacking.XFrameOptionsMiddleware',
]

ROOT_URLCONF = 'lab1.urls'

TEMPLATES = [
    {
        'BACKEND': 'django.template.backends.django.DjangoTemplates',
        'DIRS': [],
        'APP_DIRS': True,
        'OPTIONS': {
            'context_processors': [
                'django.template.context_processors.debug',
                'django.template.context_processors.request',
                'django.contrib.auth.context_processors.auth',
                'django.contrib.messages.context_processors.messages',
            ],
        },
    },
]

WSGI_APPLICATION = 'lab1.wsgi.application'


# Database
# https://docs.djangoproject.com/en/5.1/ref/settings/#databases

DATABASES = {
    'default': {
        'ENGINE': 'django.db.backends.postgresql', # <<< Адаптер связывающий орм джанго с постгресом; pip install psycopg[binary, pool]
        'NAME': 'lab1_db', # <<< Название БД
        'USER': 'django', # <<< Внутенний пользователь БД, нужно создать вручную или скриптом 
        'PASSWORD': 'django_password', # <<< Пароль юзера
        'HOST': 'localhost', # <<< тут установлен postgres-service, чтобы сервис бекенда подружился с сервисом постгреса. Изначально было localhost)
        'PORT': 5432, # <<< 
    }
}

# Password validation
# https://docs.djangoproject.com/en/5.1/ref/settings/#auth-password-validators

AUTH_PASSWORD_VALIDATORS = [
    {
        'NAME': 'django.contrib.auth.password_validation.UserAttributeSimilarityValidator',
    },
    {
        'NAME': 'django.contrib.auth.password_validation.MinimumLengthValidator',
    },
    {
        'NAME': 'django.contrib.auth.password_validation.CommonPasswordValidator',
    },
    {
        'NAME': 'django.contrib.auth.password_validation.NumericPasswordValidator',
    },
]


# Internationalization
# https://docs.djangoproject.com/en/5.1/topics/i18n/

LANGUAGE_CODE = 'en-us'

TIME_ZONE = 'UTC'

USE_I18N = True

USE_TZ = True


# Static files (CSS, JavaScript, Images)
# https://docs.djangoproject.com/en/5.1/howto/static-files/

STATIC_URL = 'static/'

# Default primary key field type
# https://docs.djangoproject.com/en/5.1/ref/settings/#default-auto-field

DEFAULT_AUTO_FIELD = 'django.db.models.BigAutoField'

# > НАША ТЕСТОВАЯ КОНСТАНТА (ЕЕ ВЫЗЫВАЕМ В VIEWS.PY)
THE_CAT = "this is the cat"