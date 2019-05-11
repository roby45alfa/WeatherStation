package com.example.meltingsoftweather;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.content.Intent;

public class MainActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
    }

    public void switchWeather(View view) {
        Intent weather = new Intent(this, weather.class);
        startActivity(weather);

    }

    public void switchCrediti(View view) {
        Intent credits = new Intent(this, crediti.class);
        startActivity(credits);
    }
}
