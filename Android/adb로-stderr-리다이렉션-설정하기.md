```bash
adb shell stop                           
adb shell setprop log.redirect-stdio true
adb shell start
```

기본적으로 안드로이드는 stderr을 `/dev/null`로 라다이렉트한다. 에러 로그를 리다이렉트 하지 않고 출력시켜서 `adb logcat`으로 확인할 수 있도록 하는 설정이다.

참고 : https://developer.android.com/studio/command-line/logcat.html?hl=ko
