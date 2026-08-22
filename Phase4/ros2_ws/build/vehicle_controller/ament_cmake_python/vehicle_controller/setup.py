from setuptools import find_packages
from setuptools import setup

setup(
    name='vehicle_controller',
    version='0.0.0',
    packages=find_packages(
        include=('vehicle_controller', 'vehicle_controller.*')),
)
