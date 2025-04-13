package org.qtproject.example.GazMonitoringApp;

import android.app.Activity;
import android.content.Intent;
import android.speech.RecognizerIntent;
import android.speech.SpeechRecognizer;
import android.speech.RecognitionListener;
import android.os.Bundle;
import android.util.Log;
import java.util.ArrayList;

public class SpeechRecognizerHelper {
    private static SpeechRecognizer speechRecognizer = null;
    private static Activity mActivity = null;

    public static void init(Activity activity) {
        mActivity = activity;
        if (SpeechRecognizer.isRecognitionAvailable(activity)) {
            speechRecognizer = SpeechRecognizer.createSpeechRecognizer(activity);
            speechRecognizer.setRecognitionListener(new RecognitionListener() {
                @Override
                public void onReadyForSpeech(Bundle params) {
                    Log.d("SpeechRecognizer", "Ready for speech");
                }

                @Override
                public void onBeginningOfSpeech() {
                    Log.d("SpeechRecognizer", "Speech beginning");
                }

                @Override
                public void onRmsChanged(float rmsdB) {
                    // Սա կարելի է թողնել դատարկ, եթե չէ պահանջվում
                }

                @Override
                public void onBufferReceived(byte[] buffer) {
                    // Չհաջորդում ենք buffer-ի հետ որևէ պրոցես
                }

                @Override
                public void onEndOfSpeech() {
                    Log.d("SpeechRecognizer", "Speech ended");
                }

                @Override
                public void onError(int error) {
                    Log.e("SpeechRecognizer", "Error: " + error);
                }

                @Override
                public void onResults(Bundle results) {
                    ArrayList<String> matches = results.getStringArrayList(SpeechRecognizer.RESULTS_RECOGNITION);
                    if (matches != null && !matches.isEmpty()) {
                        String recognizedText = matches.get(0);
                        // Այստեղ կանչում ենք մեր bridge class-ի native method-ի միջոցով
                        SpeechResultHandler.onSpeechResult(recognizedText);
                    }
                }

                @Override
                public void onPartialResults(Bundle partialResults) {
                    // Եթե ներառում եք պարշլ, կարելի է դիտարկել
                }

                @Override
                public void onEvent(int eventType, Bundle params) {
                    // Չհաջորդում ենք ըստ այս դեպության
                }
            });
        } else {
            Log.e("SpeechRecognizer", "Speech recognition is not available on this device.");
        }
    }

    public static void startListening() {
        if (mActivity != null && speechRecognizer != null) {
            Intent intent = new Intent(RecognizerIntent.ACTION_RECOGNIZE_SPEECH);
            intent.putExtra(RecognizerIntent.EXTRA_LANGUAGE_MODEL, RecognizerIntent.LANGUAGE_MODEL_FREE_FORM);
            // Օգտագործում ենք հայերէն:
            intent.putExtra(RecognizerIntent.EXTRA_LANGUAGE, "hy-AM");
            intent.putExtra(RecognizerIntent.EXTRA_PROMPT, "Խոսեք, խնդրում եմ...");
            speechRecognizer.startListening(intent);
        }
    }
}
