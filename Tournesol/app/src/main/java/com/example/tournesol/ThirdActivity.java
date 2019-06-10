package com.example.tournesol;

import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.util.Log;
import android.view.View;
import android.widget.EditText;
import android.widget.TextView;

import com.android.volley.Request;
import com.android.volley.RequestQueue;
import com.android.volley.Response;
import com.android.volley.VolleyError;
import com.android.volley.toolbox.StringRequest;
import com.android.volley.toolbox.Volley;

import org.json.JSONException;
import org.json.JSONObject;


public class ThirdActivity extends AppCompatActivity {

    TextView textMeteo;
    String city_name;
    String key ;


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_third);
        textMeteo = findViewById(R.id.Meteo);

        EditText editText = (EditText) findViewById(R.id.Ville);
        city_name = editText.getText().toString();
    }

    public void telechargerMeteo(View view){

        key = " c4d3e7d9c15ad884d512bab2919b2d7b";
        EditText editText = (EditText) findViewById(R.id.Ville);
        city_name = editText.getText().toString();

        String url = "http://api.openweathermap.org/data/2.5/weather?q="+city_name+"&APPID=c4d3e7d9c15ad884d512bab2919b2d7b";

        RequestQueue rqqueue = Volley.newRequestQueue(this);
        Response.Listener<String> responseListener = new MeteoResponseListener();
        Response.ErrorListener errRepListener = new MeteoErrorResponseListener();
        StringRequest stringRequest = new StringRequest(Request.Method.GET, url, responseListener, errRepListener);
        rqqueue.add(stringRequest);
    }

    private class MeteoResponseListener implements Response.Listener<String> {

        public void onResponse(String response){
            JSONObject jsonObject = null;
            try {
                jsonObject = new JSONObject(response);
                Log.i("coucou","coucou");
                //String temps = jsonObject.getString("weather.main");
                //String temperature = jsonObject.getString("main.temp");
                String temps = jsonObject.getJSONArray("weather").getJSONObject(0).get("main").toString();
                String temperature = jsonObject.getJSONObject("main").get("temp").toString();
                textMeteo.setText(temps+" ,"+temperature);

                //textMeteo.setText(temperature);
            } catch(JSONException e){
                e.printStackTrace();
                textMeteo.setText("pbm avec meteo");
            }
        }
    }

    private class MeteoErrorResponseListener implements Response.ErrorListener {

        public void onErrorResponse(VolleyError error){
            textMeteo.setText("error");

        }
    }

}
