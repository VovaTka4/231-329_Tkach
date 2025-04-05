from django.shortcuts import render

# > ИСПОЛЬЗОВАНИЕ НАШЕЙ КОНСТАНТЫ ВО ВЬЮС НАПРИМЕР
from django.conf import settings

from rest_framework import viewsets

from .models import Nails
from .serializers import NailsSerializer

class NailsViewSet (viewsets.ModelViewSet):
    queryset = Nails.objects.all()            # тут можно Nails.objects.filter(id=10) например чтоб только с 10ым ID, там можно и более
                                              # смешные выражения django query language
    serializer_class = NailsSerializer
    
    def create(self, request, *args, **kwargs):
        return super().create(request, *args, **kwargs)
    
    def retrieve(self, request, *args, **kwargs):
        return super().retrieve(request, *args, **kwargs)
    
    def update(self, request, *args, **kwargs):
        return super().update(request, *args, **kwargs)
    
    def partial_update(self, request, *args, **kwargs):
        return super().partial_update(request, *args, **kwargs)
    
    def destroy(self, request, *args, **kwargs):
        return super().destroy(request, *args, **kwargs)