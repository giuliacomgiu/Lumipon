package desagreg.example.com.lumipon;

import android.content.Intent;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.ListView;

import java.util.ArrayList;

public class MainActivity extends AppCompatActivity {
    ListView listitem;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        ArrayList<String> itens = new ArrayList<>();
        itens.add("Controle Remoto");
        itens.add("Parâmetros");
        itens.add("Timeline");
        listitem = (ListView) findViewById(R.id.mainlist);
        final ArrayAdapter<String> arrayAdapter = new ArrayAdapter<>
                (this, android.R.layout.simple_list_item_1, itens);
        listitem.setAdapter(arrayAdapter);
        listitem.setClickable(true);
        listitem.setOnItemClickListener(new AdapterView.OnItemClickListener() {
            @Override
            public void onItemClick(AdapterView<?> parent, View view, int position, long id) {
                Object o = parent.getItemAtPosition(position);
                String choosed  = o.toString();
                if(choosed.equals("Controle Remoto")){
                    Intent newact = new Intent(MainActivity.this,Ctrl.class);
                    startActivity(newact);
                } else if(choosed.equals("Parâmetros")){
                    Intent newact = new Intent(MainActivity.this,Parametros.class);
                    startActivity(newact);
                } else if(choosed.equals("Timeline")){
                    Intent newact = new Intent(MainActivity.this,Timeline.class);
                    startActivity(newact);
                }

            }
        });
    }
}
