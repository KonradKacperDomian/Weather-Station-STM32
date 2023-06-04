package com.weather_station

import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.util.Log
import android.widget.Button
import android.widget.Switch
import android.widget.TextView
import org.http4k.client.WebsocketClient
import org.http4k.core.Uri

import org.http4k.client.JavaHttpClient
import org.http4k.core.HttpHandler
import org.http4k.core.Method
import org.http4k.core.Request

class MainActivity : AppCompatActivity() {

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)
        var temp = 0.0
        var pressure = 0.0
        var huminity = 0.0
        val temp_switch = findViewById<Switch>(R.id.Change_Unit)
        val temp_text = findViewById<TextView>(R.id.temp)
        val presure_text = findViewById<TextView>(R.id.Pressure)
        val huminity_text = findViewById<TextView>(R.id.Huminity)
        val refresh_btn = findViewById<Button>(R.id.button5)



        refresh_btn.setOnClickListener {
            val client = WebsocketClient.blocking(Uri.of("ws://192.168.10.1:8080"))
            val text = client.received()
            Log.d("WS", "Get mesenge: $text")
            val array = text.toString().split("_")
            if (array.size == 3) {
                temp = (array[0].split(":"))[1].toDouble()
                pressure = (array[1].split(":"))[1].toDouble()
                huminity = (array[2].split(":"))[1].toDouble()
                presure_text.setText("$pressure Pha")
                huminity_text.setText("$huminity %")
                temp_text.setText("$temp°C")
            } else {
                presure_text.setText("error")
                huminity_text.setText("error")
                temp_text.setText("error")
                temp_switch.isChecked = false
            }
        }

        temp_switch.setOnCheckedChangeListener({ _, isChecked ->
            if (temp != 0.0) {
                if (isChecked) {
                    temp = (temp * 9 / 5) + 32
                    temp_text.setText("$temp°F")
                }
                else{
                    temp = (temp / (9 / 5)) - 32
                    temp_text.setText("$temp°C")
                }
            }
        })
    }
}