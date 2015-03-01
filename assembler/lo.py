# _*_ coding: UTF-8 _*_

'''Demostración de como funciona el módulo ctypes con una dll'''

# script para python 2.7.x ya nos preparamos para la migración
# a python 3 con la inclusión de __future__

from __future__ import print_function 

if __name__ == '__main__':
    import sys
    from ctypes import cdll, cast, c_int, c_float, POINTER, pointer
    # from ctypes import cdll, CDLL, cast, c_int, c_float, POINTER, pointer

    def main():
        #verificar que la versión de python sea la misma que la de nuestra dll
        #la dll fue compilada en un compilador que genera código a 32 bits
        if not 'AMD64' in sys.version:
            #lib = cdll.LoadLibrary('E:/portableapps/Dev-CppPortable/assembler/assembler.dll')
            #lib = CDLL('E:/portableapps/Dev-CppPortable/assembler/assembler.dll')
            #lib = CDLL('assembler.dll')
            lib = cdll.LoadLibrary('assembler.dll')
            #lib.HelloWorld()
            print(lib.suma(1, 1))
            print(lib.multiplica(1000, 2))
            ##################################################
            # register_or_real_value = lib.fmultiplica(c_float(2.5), c_float(0.5))
            # int_pointer = (c_int*1)(register_or_real_value)
            # float_pointer = cast(int_pointer, POINTER(c_float))
            # float_number = float_pointer[0]
            # print float_number
            ##################################################
            # return_value = lib.fmultiplica(c_float(2.5), c_float(0.5))
            # int_pointer = pointer(c_int(return_value))
            # float_pointer = cast(int_pointer, POINTER(c_float))
            # float_number = float_pointer[0]
            # print float_number
            ##################################################
            ## he aquí unos ejemplo de como parsear un registro que contiene
            ## un "número float", dejando ejecutar el último
            ##################################################
            # int_pointer = pointer(c_int(lib.fmultiplica(c_float(2.5), c_float(0.5))))
            # float_pointer = cast(int_pointer, POINTER(c_float))
            # float_number = float_pointer[0]
            # print float_number
            ##################################################
            # int_pointer = pointer(c_int(lib.fmultiplica(c_float(2.5), c_float(0.5))))
            # print cast(int_pointer, POINTER(c_float))[0]
            ###################################################
            args = (2.5, 0.5)
            func_float_args = (c_float(args[0]), c_float(args[1]))
            ret_value = lib.fmultiplica(func_float_args) # register value, not coded like float
            int_pointer = pointer(c_int(ret_value)) # neccesary to cast into float value
            float_pointer = cast(int_pointer, POINTER(c_float)) # cast
            real_float_value = float_pointer[0]
            print(real_float_value)
            ###################################################
            #lib.smultiplica("2.8", "2")
            #print lib.sdivide('5.0', '2.9')
        else:
            print('consigue una versión python a 32 bits')

    main()
