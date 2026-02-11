package com.example.base64jni;

import android.os.Bundle;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;

import androidx.activity.EdgeToEdge;
import androidx.appcompat.app.AppCompatActivity;
import androidx.core.graphics.Insets;
import androidx.core.view.ViewCompat;
import androidx.core.view.WindowInsetsCompat;

public class MainActivity extends AppCompatActivity {

    static {
       System.loadLibrary("base64jni");
    }

    public native String b64Encode(String input);
    public native String b64Decode(String input);


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        EdgeToEdge.enable(this);
        setContentView(R.layout.activity_main);

        Button encodeBtn = findViewById(R.id.bencode);
        Button decodeBtn = findViewById(R.id.bdecode);
        EditText userInput = findViewById(R.id.userInput);
        TextView outputText = findViewById(R.id.outputText);


        encodeBtn.setOnClickListener(v->{

            String inputString = userInput.getText().toString();
            String result = b64Encode(inputString);
            outputText.setText(result);

        });

        decodeBtn.setOnClickListener(v->{
            String inputString = userInput.getText().toString();
            String result = b64Decode(inputString);
            outputText.setText(result);
        });


        ViewCompat.setOnApplyWindowInsetsListener(findViewById(R.id.main), (v, insets) -> {
            Insets systemBars = insets.getInsets(WindowInsetsCompat.Type.systemBars());
            v.setPadding(systemBars.left, systemBars.top, systemBars.right, systemBars.bottom);
            return insets;
        });
    }
}