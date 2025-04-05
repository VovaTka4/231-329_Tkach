from django.db import models

# Create your models here.

class Nails(models.Model): 
    datetime_shipment = models.DateTimeField(null = True)
    datetime_sending = models.DateTimeField(null = True)
    typename = models.CharField(max_length = 50, null = True)
    serialNum = models.CharField(max_length = 10, null = True)
    material = models.CharField(max_length=15, null = True)