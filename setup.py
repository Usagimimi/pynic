from distutils.core import setup, Extension
 
module1 = Extension('pyiface',
                    define_macros = [('MAJOR_VERSION', '0'),
                                     ('MINOR_VERSION', '2')], 
                    sources = ['src/pyiface.c', 'src/iface.c'])
 
setup(name = 'pyIface',
      version = '0.2',
      description = 'It is an interface to get NIC information',
      author = 'Alfredo Miranda',
      author_email = 'alfredocdmiranda@gmail.com',
      url = 'https://github.com/alfredocdmiranda/pyIface',
      license='GPL v3',
      long_description='It is an interface to get NIC information',
      ext_modules = [module1])
