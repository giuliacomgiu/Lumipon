package desagreg.example.com.lumipon;

import android.content.Context;
import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.text.InputType;
import android.util.Log;
import android.view.KeyEvent;
import android.view.View;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.EditText;
import android.widget.Spinner;
import android.widget.Switch;
import android.widget.TextView;

import org.json.JSONObject;

import java.io.File;
import java.text.DateFormat;
import java.text.SimpleDateFormat;
import java.util.Date;

/**
 * Created by claudio on 24/04/2017.
 */

public class Parametros extends AppCompatActivity {
    Contexto cont1,cont2;
    int lamp = 0;
    @Override
    protected void onCreate(Bundle savedInstancestates) {
        super.onCreate(savedInstancestates);
        setContentView(R.layout.parametros);
        File file = new File(getBaseContext().getFilesDir(),getString(R.string.myfilename));
        file.setWritable(true);
        file.setReadable(true);
        /* DEBUG ONLY */
        boolean canread = file.canRead();
        boolean canwrite = file.canWrite();
        Log.e(Boolean.toString(canread),"canread");
        Log.e(Boolean.toString(canread),"canwrite");
        /* DEBUG ONLY */
        final TextView planttextview = (TextView) findViewById(R.id.textView3);
        final TextView timetextview = (TextView) findViewById(R.id.textView4);
        planttextview.setVisibility(View.GONE);
        timetextview.setVisibility(View.GONE);
        cont1 = new Contexto();
        cont2 = new Contexto();
        final EditText Plantatext = (EditText) findViewById(R.id.editText);
        final EditText TimeText = (EditText) findViewById(R.id.editText2);
        TimeText.setInputType(InputType.TYPE_DATETIME_VARIATION_TIME);
        //como receber o valor de tempo ideal pra planta
        Plantatext.setOnEditorActionListener(new TextView.OnEditorActionListener() {
            @Override
            public boolean onEditorAction(TextView v, int actionId, KeyEvent event) {
                boolean change_values = false;
                change_values = Plantname(lamp,(String)v.getText().toString());
                //Log.e("OLHAAAA ai",);
                return change_values;
            }
        });
        TimeText.setOnEditorActionListener(new TextView.OnEditorActionListener(){
                boolean change_values = false;
                long time = 0;
            @Override
            public  boolean onEditorAction(TextView v,int actionId, KeyEvent event){
                String temp = v.toString();
                DateFormat format = new SimpleDateFormat("hh:mm");
                try {
                        Date date = format.parse(temp);
                    change_values = RightTime(lamp,date);
                    return change_values;
                } catch (java.text.ParseException e){
                    Log.e("Deu merda",e.toString());
                    return false;
                }
            }

        });
        TimeText.setVisibility(View.GONE);
        Plantatext.setVisibility(View.GONE);
        Spinner spinner = (Spinner) findViewById(R.id.spinner);
        ArrayAdapter<CharSequence> adapter = ArrayAdapter.createFromResource(this, R.array.spinner_array,
                android.R.layout.simple_spinner_item);
        adapter.setDropDownViewResource(android.R.layout.simple_spinner_dropdown_item);
        spinner.setAdapter(adapter);
        spinner.setOnItemSelectedListener(new AdapterView.OnItemSelectedListener() {
            @Override
            public void onItemSelected(AdapterView<?> parent, View view, int position, long id) {
                Object o = parent.getSelectedItem();
                String selected = o.toString();
                if(selected.equals("Lampada1")){
                 lamp = 1;
                 planttextview.setText("Planta 1");
                 planttextview.setVisibility(View.VISIBLE);
                 timetextview.setVisibility(View.VISIBLE);
                }else if(selected.equals("Lampada2")){
                 lamp = 2;
                    planttextview.setText("Planta 2");
                    planttextview.setVisibility(View.VISIBLE);
                    timetextview.setVisibility(View.VISIBLE);
                }
                Plantatext.setVisibility(View.VISIBLE);
                TimeText.setVisibility(View.VISIBLE);
            }

            @Override
            public void onNothingSelected(AdapterView<?> parent) {
                TimeText.setVisibility(View.GONE);
                Plantatext.setVisibility(View.GONE);
            }
        });
    }


    @Override
    public void onStart() {
        super.onStart();

    }
 public boolean Plantname(int lamp,String text){
     if(lamp == 1) {
         //TextView tx = (TextView) findViewById(R.id.textView4);
         cont1.mylamp = lamp;
         cont1.plantname = text;
        // tx.setText(cont1.plantname + Integer.toString(cont1.mylamp));
         //enviar contexto para o serviço e depois manda-lo para o DB
     } else if(lamp == 2){
         cont2.mylamp = lamp;
         cont2.plantname = text;
     }
     return false;
 }
  boolean RightTime(int lamp,Date time){
      if(lamp == 1){
          //cont1.time = time;
      }else if(lamp == 2){
          //cont2.time = time;
      }
      return false;
  }

public class Contexto{
    //salvar classe contexto na memoria e inicializar seus valores antigos no onCreate
    private int mylamp;
    private String plantname;
    private long time;
    Contexto(){
        mylamp = 0;
        plantname = null;
        time = 0;
    }
}
private JSONObject ConvertToJson(){

    return null;
}

}