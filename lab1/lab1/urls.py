"""
КОНСПЕКТ:
# Содержит в себе элементы URL, обрабатываемые данным бэкендом и функции методы, которые овтечают за обработку запросов
"""

from django.contrib import admin
from django.urls import path

from rest_framework import routers

from mainapp.views import NailsViewSet

urlpatterns = [
    path('admin/', admin.site.urls),
    #       URL                       {Метод HTTP: Метод Класса, ...и тд...}
    path('nails/', NailsViewSet.as_view({'get': 'list', 'post': 'create'})),
    path('nails/<pk>', NailsViewSet.as_view({'get': 'retrieve', 'put': 'update', 'patch': 'partial_update', 'delete': 'destroy'})),
]
