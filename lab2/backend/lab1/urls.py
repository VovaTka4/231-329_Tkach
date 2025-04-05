"""
КОНСПЕКТ:
# Содержит в себе элементы URL, обрабатываемые данным бэкендом и функции методы, которые овтечают за обработку запросов
"""

from django.contrib import admin
from django.urls import path

from django.conf import settings
from django.conf.urls.static import static

from rest_framework import routers

from mainapp.views import NailsViewSet

urlpatterns = [
    path('admin/', admin.site.urls),
    #       URL                       {Метод HTTP: Метод Класса, ...и тд...}
    path('api/nails/', NailsViewSet.as_view({'get': 'list', 'post': 'create'})),
    path('api/nails/<pk>', NailsViewSet.as_view({'get': 'retrieve', 'put': 'update', 'patch': 'partial_update', 'delete': 'destroy'})),
]

urlpatterns += static(settings.STATIC_URL, document_root=settings.STATIC_ROOT)