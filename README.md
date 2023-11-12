# TP-FINAL-ED3

## Autores
- Bernaus, Julieta
- Pasolli, Néstor Jeremías

## Descripción
El siguiente es un proyecto integrador para la materia Electrónica Digital III de la Universidad Nacional de Córdoba, año 2023.
Se hace uso de una placa LPC1769 de núcleo ARM Cortex M3.

En este trabajo, se presenta un prototipo funcional de una alarma casera.

### Detalles de la implementación
La misma cuenta con:
- sensores de movimiento,
- sensor de gases, 
- un teclado para su activación y desactivación, 
- comunicación Bluetooth con computadora, tanto para mostrar datos medidos como para activar y desactivarla.

## Pin-out

- P0.10 : UART - Receptor
- P0.11 : UART - Transmisor
- P0.18 : LED para mostrar estado de la alarma
- P0.23 : ADC para el sensor de gases
- P0.26 : DAC para el buzzer que provoca el sonido de alarma
- P2.0  : salida del teclado matricial
- P2.1  : salida del teclado matricial
- P2.2  : salida del teclado matricial
- P2.3  : salida del teclado matricial
- P2.4  : entrada del teclado matricial
- P2.5  : entrada del teclado matricial
- P2.6  : entrada del teclado matricial
- P2.10 : EINT0 para un sensor de movimiento
- P2.11 : EINT1 para otro sensor de movimiento
- Conexión a tierra de ambos lados de la placa
- Conexión externa a batería de 5V

![image](./lib/pin-out.png)








