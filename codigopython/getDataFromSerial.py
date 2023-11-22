# Al momento de correr este codigo cerrar la ventana de serial de arduino

# Instalar la liberia pyserial y revisar que este actualizada
import serial
import time
from collections import deque
import warnings
import itertools
import csv

#windows usa puertos COM, revisar cual es el del puerto usb
#Linux nativo utiliza puertos de nombre TTYACM
hw_sensor = serial.Serial(port='COM3', baudrate=9600)
hw_sensor.setDTR(False)
time.sleep(.1)
hw_sensor.flushInput()
hw_sensor.setDTR(True)

#Producir los archivos .csv para cada cara, 5 pases de 120 muestras, es decir 600 muestras por cara
#Esta seccion es para nombrar el archivo de salida en el formato label+count_file. EJ Side_face_1.csv. Cambiar para evitar confusoiones
label = 'side_face'
count_file = 1
#count_file = 2
#count_file = 3
#count_file = 4
#count_file = 5
#count_file = 6
#Cubo en movimiento#
#count_file = 0 

M = []
data = []

f = open(f'{label}_{count_file}.csv', 'a')
w = csv.writer(f)

# nombres de columnas, deben corresponder en orden y posicion con el formato separado por comas que salga por serial en la placa arduino

w.writerow(['tVal2','tVal3','tVal4','tVal5','tVal6','tVal7','ax','ay','az','gx','gy','gz', 'face'])
with hw_sensor:
    while True:
        try:
            line = hw_sensor.readline()
            if not line:
                # HACK: Descartamos líneas vacías porque fromstring produce
                # resultados erróneos, ver https://github.com/numpy/numpy/issues/1714
                continue
            # M.append(np.fromstring(line.decode('ascii', errors='replace'), sep=','))
            # data.append(yy)
            tmp = line.decode('ascii', errors='replace').rstrip().split(',')
            if (len(tmp) >= 5):
                data.append(tmp)

            if (len(data) == 120):
                r = input('¿Guardar?')
                if (r == 's'):
                    for d in data:
                        w.writerow(d)
                    w.writerow([])
                data = []
        except KeyboardInterrupt:
            print("Exiting")
            break

# Cada ciclo antes de la pregunta Guardar son 120 muestras, el programa sigue ejecutandose y tomando muestras hasta
# que se interrumpe con ctrl c

# Desconozco el porque pero en windows el archivo .csv no se guarda en el directorio donde este programa se ejecuta.
# Buscar el .csv en raiz