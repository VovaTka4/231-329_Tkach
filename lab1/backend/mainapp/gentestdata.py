import random, string, datetime, os, django

from django.db import transaction
from faker import Faker
from .models import *


fk = Faker()

def gentestdata():
    with transaction.atomic():
        for i in range(1000):
            newNail = Nails()
            newNail.datetime_shipment = fk.date_between(start_date=datetime.date(2000,1,1), end_date=datetime.date(2025,1,1))
            newNail.datetime_sending = fk.date_between(start_date=newNail.datetime_shipment, end_date = datetime.datetime.now().date())
            newNail.typename = 'Type'+str(random.randint(1, 50))
            newNail.material = random.choice(('Steel', 'Iron', 'Copper', 'Aluminum', 'Titanium'))
            newNail.serialNum = ''.join(random.sample(string.ascii_letters + string.digits, 5))
            
            newNail.save()
    # <<< транзакция закончилась
    print('ОК')
    
def cleardata():
    Nails.objects.all().delete()
    
if __name__ == '__main__':
    gentestdata()        