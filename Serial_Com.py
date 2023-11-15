import tkinter as tk
import serial

class SerialApp:
    def __init__(self, master):
        self.master = master
        self.master.title("Aplicación Serial")
        self.master.geometry("400x300")

        # Variable para almacenar el texto completo recibido
        self.texto_completo_var = tk.StringVar()

        # Configurar la comunicación serie (ajusta el puerto COM según tu configuración)
        self.serial_port = serial.Serial('COM3', 9600, timeout=1)

        # Crear widgets
        self.create_widgets()

    def create_widgets(self):
        # Recuadro para mostrar el texto completo recibido
        texto_label = tk.Label(self.master, text="Texto Recibido:")
        texto_label.grid(row=0, column=0, padx=10, pady=10, sticky=tk.W)

        texto_entry = tk.Entry(self.master, textvariable=self.texto_completo_var, state="readonly", width=30)
        texto_entry.grid(row=0, column=1, padx=10, pady=10)

        # Configurar la actualización periódica de los datos
        self.master.after(100, self.actualizar_datos)

    def actualizar_datos(self):
        # Intentar leer datos de la comunicación serie
        try:
            data = self.serial_port.readline().decode('utf-8').strip()
            if data:
                # Almacenar el texto completo recibido
                self.texto_completo_var.set(data)
        except serial.SerialException:
            print("Error de lectura en el puerto serie")

        # Configurar la actualización periódica de los datos
        self.master.after(100, self.actualizar_datos)

if __name__ == "__main__":
    root = tk.Tk()
    app = SerialApp(root)
    root.mainloop()
