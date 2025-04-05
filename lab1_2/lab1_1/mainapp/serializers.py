# Нужен чтобы преобразовывать модели в JSON и обратно
# для API, Django Rest framework 

from rest_framework import serializers

from .models import Nails

class NailsSerializer(serializers.ModelSerializer):
   
    class Meta:
        model = Nails
        fields = '__all__' # <= список полей которые будут учитываться, если все поля то __all__ все поля модели идентичны полям json
        # exclude  <= какие поля игнорируются