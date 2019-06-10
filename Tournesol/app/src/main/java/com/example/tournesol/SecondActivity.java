package com.example.tournesol;


import android.content.Context;
import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.view.View;
import android.widget.ImageView;

public class SecondActivity extends AppCompatActivity implements View.OnClickListener {

    private int numeroImage = 5 ;
    ImageView imageTransat ;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_second);
    }

    public void onClick(View v){

    }

    public void tournerGauche(View v){

        imageTransat = (ImageView)findViewById(R.id.imageViewTransat);
        String nameImage;

        // define next image
        if(numeroImage == 1){
            numeroImage = 10;
        }else {
            numeroImage--;
        }
        nameImage = "image"+numeroImage;

        // display next image
        Context context = imageTransat.getContext();
        int id = context.getResources().getIdentifier(nameImage, "drawable",
                context.getPackageName());
        imageTransat.setImageResource(id);
    }

    public void tournerDroite(View v){
        imageTransat = (ImageView)findViewById(R.id.imageViewTransat);
        String nameImage;

        // define next image
        if(numeroImage == 10){
            numeroImage = 1;
        }else {
            numeroImage++;
        }
        nameImage = "image"+numeroImage;

        // display next image
        Context context = imageTransat.getContext();
        int id = context.getResources().getIdentifier(nameImage, "drawable",
                context.getPackageName());
        imageTransat.setImageResource(id);
    }


}

