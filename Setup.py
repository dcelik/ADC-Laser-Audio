from distutils.core import setup, Extension

module1 = Extension('fgp',
                    sources = ['fastgpio.c'])

setup (name = 'FastGPIO',
       version = '1.0',
       description = 'This is a fastGpio package for raspi',
       ext_modules = [module1])