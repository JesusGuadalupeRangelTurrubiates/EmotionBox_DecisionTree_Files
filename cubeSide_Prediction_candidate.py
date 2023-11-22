"""
#funcion de prueba. Pasar la lista de valores a funcion
def side_predtest(values_Topredict):
    print('test pred:' , values_Topredict)
"""

# Funcion de prediccion, aqui se debe poner todo el arbol
# prediction es la prediccion del lado del cubo
# Reemplazarse por algo mas representativo como "face" o "side" etc
def side_pred(t1,t2,t3,t4,t5,t6,ax,ay,az,gx,gy,gz):
    print('side_pred function flag')
    # Aqui comienza la magia
    if az <= -1.04:
        if t5 <= 0.5:
            prediction = 5
        if t5 > 0.5:
            prediction = 1
    if az > -1.04:
        if ax <= -0.515:
            if ay <= 0.685:
                if ay <= -0.72:
                    prediction = 3
                if ay > -0.72:
                    if az <= 0.86:
                        prediction = 4
                    if az > 0.86:
                        prediction = 6
            if ay > 0.685:
                prediction = 2
        if ax > -0.515:
            if ay <= -0.575:
                if ax <= 0.0585:
                    if ay <= -0.675: 
                        prediction = 3
                    if ay > -0.675: 
                        prediction = 3
                if ax > 0.0585:
                    if gx <= -295.01:
                        prediction = 3
                    if gx > -295.01:
                        prediction = 5
            if ay > -0.575:
                if ax <= 0.655:
                    if ay <= 0.685:
                        prediction = 6
                    if ay > 0.685:
                        prediction = 2
                if ax > 0.655:
                    if az <= 0.295:
                        prediction = 5
                    if az > 0.295:
                        prediction = 5
                                                                
    return prediction

#input_string = input('Enter elements of a list separated by commas \n')
#Ejemplo de ingreso de datos, la prediccion deberia resultar en la cara 1
#input_string = '0,1,0,0,1,1,-0.08,0.07,-1.19,-235.73,4220.85,-342.43' 
#input_string = ' 1,	1,	1,	1,	1,	0,	-0.30,	-0.39,	0.61,	658.17,	421.55,	378.33' # clase 6 / cara 6

input_string = '1,1,1,1,1,1,0.09,-0.07,0.88,1438.93,-32.62,27.18'
#input_string = '1,	0,	1,	1,	1,	1,	-0.09,	0.65,	-0.76,	-2853.74,	-311.17,	24.79' #clase 2 / cara 2
#input_string = '1,	0,	1,	1,	1,	0,	-0.03,	0.85,	0.26,	-3294.97,	-437.06,	581.84' #768, clase 2
input_list = input_string.split(',')

# convertir a flotantes
for i in range(len(input_list)): 
    # convert each item to float
    input_list[i] = float(input_list[i])

print('input values: ', input_list) #mostrar de entrada
#asignar los elementos de la lista de datos en variables separadas
t1,t2,t3,t4,t5,t6,ax,ay,az,gx,gy,gz = [input_list[i] for i in range(12)]

#side_predtest(input_list)

#Enviar datos a la funcion de prediccion
print('Prediccion: ' , side_pred(t1,t2,t3,t4,t5,t6,ax,ay,az,gx,gy,gz))
#print(side_pred(t1,t2,t3,t4,t5,t6,ax,ay,az,gx,gy,gz))
