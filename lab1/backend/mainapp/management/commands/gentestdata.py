from django.core.management.base import BaseCommand
import random
import string
import datetime
from faker import Faker
from mainapp.models import Nails

class Command(BaseCommand):

    def handle(self, *args, **options):
        
        if Nails.objects.count() == 0:
            fk = Faker()

            for i in range(1000):
                new_nail = Nails(
                    datetime_shipment=fk.date_between(start_date=datetime.date(2000, 1, 1), end_date=datetime.date(2025, 1, 1)),
                    datetime_sending=fk.date_between(start_date=datetime.date(2000, 1, 1), end_date=datetime.datetime.now().date()),
                    typename='Type' + str(random.randint(1, 50)),
                    material=random.choice(['Steel', 'Iron', 'Copper', 'Aluminum', 'Titanium']),
                    serialNum=''.join(random.sample(string.ascii_letters + string.digits, 5)),
                )
                new_nail.save()

            self.stdout.write(self.style.SUCCESS('Successfully generated data'))
        else:
            self.stdout.write(self.style.WARNING('Database is not empty. Skipping data generation.'))