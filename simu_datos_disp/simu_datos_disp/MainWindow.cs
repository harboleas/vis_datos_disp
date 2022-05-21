using System;
using Gtk;
using System.IO;
using System.IO.Ports;
using System.Threading;

public partial class MainWindow : Gtk.Window
{

    private SerialPort port;
    private byte[] trama = new byte[7];
    public MainWindow() : base(Gtk.WindowType.Toplevel)
    {
        Build();

        //Conexion con arduino
        port = new SerialPort("/dev/ttyUSB0", 115200);
        port.Open();

    }

    protected void OnDeleteEvent(object sender, DeleteEventArgs a)
    {
        Application.Quit();
        a.RetVal = true;
        if (port.IsOpen)
            port.Close();
    }

    protected void OnButtonUpdateClicked(object sender, EventArgs e)
    {

        // Armado de la trama con los datos 
        // Sync 1 y 2
        trama[0] = 0xff;
        trama[1] = 0xff;

        // Velocidad 
        ushort Vel = ushort.Parse(vel.Text);
        trama[2] = BitConverter.GetBytes(Vel)[0];
        trama[3] = BitConverter.GetBytes(Vel)[1];

        // Disparos
        ushort Cant = ushort.Parse(cant.Text);
        trama[4] = BitConverter.GetBytes(Cant)[0];
        trama[5] = BitConverter.GetBytes(Cant)[1];

        // Verificacion de errores
        byte verif = (byte) (trama[2] + trama[3] + trama[4] + trama[5]);
        if (verif == 0xff)
            verif = 0xfe;
        if (button_error_com.Active)
            verif += 2;
        trama[6] = verif;

        // Envia la trama
        port.Write(trama, 0, 7);
    
    }
}
