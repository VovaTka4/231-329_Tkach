from django.contrib import admin
from mainapp.models import Nails

@admin.register(Nails)
class NailsAdmin(admin.ModelAdmin):
    list_display = ("id", "typename", "serialNum", "material", "datetime_shipment", "datetime_sending")