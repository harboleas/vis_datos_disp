
// This file has been generated by the GUI designer. Do not modify.

public partial class MainWindow
{
	private global::Gtk.Fixed fixed1;

	private global::Gtk.Label label1;

	private global::Gtk.Label label2;

	private global::Gtk.Entry vel;

	private global::Gtk.Entry cant;

	private global::Gtk.CheckButton button_error_com;

	private global::Gtk.Button button_update;

	protected virtual void Build()
	{
		global::Stetic.Gui.Initialize(this);
		// Widget MainWindow
		this.Name = "MainWindow";
		this.Title = global::Mono.Unix.Catalog.GetString("Simulador de datos del disparo");
		this.WindowPosition = ((global::Gtk.WindowPosition)(4));
		// Container child MainWindow.Gtk.Container+ContainerChild
		this.fixed1 = new global::Gtk.Fixed();
		this.fixed1.Name = "fixed1";
		this.fixed1.HasWindow = false;
		// Container child fixed1.Gtk.Fixed+FixedChild
		this.label1 = new global::Gtk.Label();
		this.label1.Name = "label1";
		this.label1.LabelProp = global::Mono.Unix.Catalog.GetString("Velocidad :");
		this.fixed1.Add(this.label1);
		global::Gtk.Fixed.FixedChild w1 = ((global::Gtk.Fixed.FixedChild)(this.fixed1[this.label1]));
		w1.X = 128;
		w1.Y = 101;
		// Container child fixed1.Gtk.Fixed+FixedChild
		this.label2 = new global::Gtk.Label();
		this.label2.Name = "label2";
		this.label2.LabelProp = global::Mono.Unix.Catalog.GetString("Disparos : ");
		this.fixed1.Add(this.label2);
		global::Gtk.Fixed.FixedChild w2 = ((global::Gtk.Fixed.FixedChild)(this.fixed1[this.label2]));
		w2.X = 130;
		w2.Y = 149;
		// Container child fixed1.Gtk.Fixed+FixedChild
		this.vel = new global::Gtk.Entry();
		this.vel.CanFocus = true;
		this.vel.Name = "vel";
		this.vel.Text = global::Mono.Unix.Catalog.GetString("0");
		this.vel.IsEditable = true;
		this.vel.InvisibleChar = '●';
		this.fixed1.Add(this.vel);
		global::Gtk.Fixed.FixedChild w3 = ((global::Gtk.Fixed.FixedChild)(this.fixed1[this.vel]));
		w3.X = 209;
		w3.Y = 93;
		// Container child fixed1.Gtk.Fixed+FixedChild
		this.cant = new global::Gtk.Entry();
		this.cant.CanFocus = true;
		this.cant.Name = "cant";
		this.cant.Text = global::Mono.Unix.Catalog.GetString("0");
		this.cant.IsEditable = true;
		this.cant.InvisibleChar = '●';
		this.fixed1.Add(this.cant);
		global::Gtk.Fixed.FixedChild w4 = ((global::Gtk.Fixed.FixedChild)(this.fixed1[this.cant]));
		w4.X = 209;
		w4.Y = 140;
		// Container child fixed1.Gtk.Fixed+FixedChild
		this.button_error_com = new global::Gtk.CheckButton();
		this.button_error_com.CanFocus = true;
		this.button_error_com.Name = "button_error_com";
		this.button_error_com.Label = global::Mono.Unix.Catalog.GetString("Error de comunicacion");
		this.button_error_com.DrawIndicator = true;
		this.button_error_com.UseUnderline = true;
		this.fixed1.Add(this.button_error_com);
		global::Gtk.Fixed.FixedChild w5 = ((global::Gtk.Fixed.FixedChild)(this.fixed1[this.button_error_com]));
		w5.X = 204;
		w5.Y = 204;
		// Container child fixed1.Gtk.Fixed+FixedChild
		this.button_update = new global::Gtk.Button();
		this.button_update.CanFocus = true;
		this.button_update.Name = "button_update";
		this.button_update.UseUnderline = true;
		this.button_update.Label = global::Mono.Unix.Catalog.GetString("Actualizar datos");
		this.fixed1.Add(this.button_update);
		global::Gtk.Fixed.FixedChild w6 = ((global::Gtk.Fixed.FixedChild)(this.fixed1[this.button_update]));
		w6.X = 230;
		w6.Y = 262;
		this.Add(this.fixed1);
		if ((this.Child != null))
		{
			this.Child.ShowAll();
		}
		this.DefaultWidth = 596;
		this.DefaultHeight = 403;
		this.Show();
		this.DeleteEvent += new global::Gtk.DeleteEventHandler(this.OnDeleteEvent);
		this.button_update.Clicked += new global::System.EventHandler(this.OnButtonUpdateClicked);
	}
}
