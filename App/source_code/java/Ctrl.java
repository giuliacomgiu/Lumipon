package desagreg.example.com.lumipon;

import android.content.Context;
import android.content.SharedPreferences;
import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.widget.CompoundButton;
import android.widget.Switch;
import android.widget.TextView;
import android.widget.Toast;

/**
 * Created by claudio on 24/04/2017.
 */

public class Ctrl extends AppCompatActivity {

    private Switch myswitch1,myswitch2;
    private boolean codecheck1,codecheck2;
    SharedPreferences sharedPref;
    SharedPreferences.Editor editor;
    @Override
    protected void onCreate(Bundle savedInstanceState){
        super.onCreate(savedInstanceState);
        setContentView(R.layout.controle_remoto);
        Context context = getBaseContext();
        sharedPref = getPreferences(Context.MODE_PRIVATE);
        codecheck1 = sharedPref.getBoolean(getString(R.string.control1_file_key),true);
        codecheck2 = sharedPref.getBoolean(getString(R.string.control2_file_key),true);
        editor = sharedPref.edit();
        myswitch1 = (Switch) findViewById(R.id.switch1);
        myswitch2 = (Switch) findViewById(R.id.switch2);
        myswitch1.setChecked(codecheck1);
        myswitch2.setChecked(codecheck2);
        //  myswitch1.setChecked(true);
        //myswitch2.setChecked(true);
    }
    @Override
    protected void onStart(){
        super.onStart();
        myswitch1.setOnCheckedChangeListener(new CompoundButton.OnCheckedChangeListener() {
            @Override
            public void onCheckedChanged(CompoundButton buttonView, boolean isChecked) {
                if(isChecked){
                    Toast.makeText(getApplicationContext(),"Algortimo  referente a lampada 1 rodando no hardware",Toast.LENGTH_LONG);
                    codecheck1 = true;
                    //fazer rotina para enviar pro serviço o valor de codecheck e tb salva-lo na memoria
                }else{
                    Toast.makeText(getApplicationContext(),"Algortimo para lampada 1 desligado hehhehe",Toast.LENGTH_LONG);
                    codecheck1 = false;
                }
                editor.putBoolean(getString(R.string.control1_file_key),codecheck1);
                editor.commit();

            }
        });
        myswitch2.setOnCheckedChangeListener(new CompoundButton.OnCheckedChangeListener() {
            @Override
            public void onCheckedChanged(CompoundButton buttonView, boolean isChecked) {
                if(isChecked){
                    Toast.makeText(getApplicationContext(),"Algortimo referente a lampada 2 rodando no hardware",Toast.LENGTH_LONG);
                    codecheck2 = true;
                }else{
                    Toast.makeText(getApplicationContext(),"Algortimo para lampada 2 desligado hehehehe",Toast.LENGTH_LONG);
                    codecheck2 = false;
                }
                editor.putBoolean(getString(R.string.control2_file_key),codecheck2);
                editor.commit();
            }
        });
    }
    @Override
    public void onDestroy(){
        super.onDestroy();
    }
}
