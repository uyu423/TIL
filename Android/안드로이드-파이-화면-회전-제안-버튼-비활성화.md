# 안드로이드 9.0 (파이) 화면 회전 제안 버튼 비활성화 하기

갤럭시 S8을 안드로이드 9.0으로 업데이트 했는데, 사소한 기능이 하나 생겼다. 자이로 센서로 화면이 돌아갔다는 것이 판단되면 오른쪽 하단에 작은 화면 회전 버튼이 하나 생기는데, 얘를 눌러서 바로 화면을 회전 시킬 수 있는 기능이다.

하지만 이 기능이 나에게는 아주 개같은 기능인 것이, 누워서 폰질하다 보면 자꾸 얘가 뜨고, 나의 평소 손가락 위치와 얘가 맞물려 자꾸 화면이 돌아가는 것이다.

현재 안드로이드 설정 내에서는 이 옵션을 키거나 끄는 메뉴는 없는 것 같고 `adb` 통해서 핸들링 가능하다.

## 끌 때
```bash
adb shell settings put secure show_rotation_suggestions 0
```

## 다시 킬 때
```bash
adb shell settings put secure show_rotation_suggestions 1
```

## +
- 기본적으로 secure show_rotation_suggestions 값은 `null` 이다.
- 기글하드웨어 포럼의 '[안드로이드 파이 화면 회전 버튼 비활성화 하기](https://gigglehd.com/gg/soft/4483266)' 는 나의 갤럭시 S8 에서 효과가 없었음.
- 참고
  - [Redit Post](https://www.reddit.com/r/GalaxyS9/comments/aotdk7/heres_how_to_disable_rotation_suggestions_on_pie/)
  - [Android Source](https://source.android.com/devices/tech/display/rotate-suggestions)