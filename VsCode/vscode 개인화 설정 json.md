# 요우의 Visual Studio Code Setting JSON

- [VsCode/초기 세팅.md](https://github.com/uyu423/TIL/blob/master/VsCode/%EC%B4%88%EA%B8%B0%20%EC%84%B8%ED%8C%85.md) 가 선행되어야하는 설정들이 포함되어 있습니다.
- ~~나는 모르겠는데 쓰다보니 자꾸 이상한 옵션이 막 생긴다~~

## settings.json (v.20200421, MacBook Pro on Workplace)

```json
{
  "workbench.colorTheme": "Material Theme",
  "editor.fontFamily": "Ubuntu Mono",
  "editor.autoIndent": "full",
  "editor.tabSize": 2,
  "editor.fontSize": 18,
  "editor.wordWrap": "on",
  "editor.rulers": [130],
  "window.zoomLevel": 0,
  "editor.formatOnSave": true,
  "vim.useSystemClipboard": true,
  "workbench.iconTheme": "material-icon-theme",
  "javascript.updateImportsOnFileMove.enabled": "always",
  "editor.codeActionsOnSave": {
    "source.fixAll.eslint": true,
    "source.fixAll.tslint": true
    // "source.organizeImports": true,
  },
  "prettier.singleQuote": true,
  "[typescript]": {
    "editor.defaultFormatter": "esbenp.prettier-vscode"
  }
}
```

## settings.json (legacy)

```json
{
  "workbench.iconTheme": "vscode-icons",
  "editor.fontFamily": "Ubuntu Mono",
  "editor.autoIndent": true,
  "editor.tabSize": 2,
  "editor.fontSize": 20,
  "editor.wordWrap": "on",
  "tslint.autoFixOnSave": true,
  "editor.rulers": [130],
  "window.zoomLevel": 0,
  "workbench.colorTheme": "Material Theme",
  "editor.formatOnSave": true,
  "vim.useSystemClipboard": true,
  "gitlens.advanced.messages": {
    "suppressCommitHasNoPreviousCommitWarning": false,
    "suppressCommitNotFoundWarning": false,
    "suppressFileNotUnderSourceControlWarning": false,
    "suppressGitVersionWarning": false,
    "suppressLineUncommittedWarning": false,
    "suppressNoRepositoryWarning": false,
    "suppressResultsExplorerNotice": false,
    "suppressShowKeyBindingsNotice": true
  },
  "workbench.colorCustomizations": {
    "activityBarBadge.background": "#C6FF00",
    "list.activeSelectionForeground": "#C6FF00",
    "list.inactiveSelectionForeground": "#C6FF00",
    "list.highlightForeground": "#C6FF00",
    "scrollbarSlider.activeBackground": "#C6FF0050",
    "editorSuggestWidget.highlightForeground": "#C6FF00",
    "textLink.foreground": "#C6FF00",
    "progressBar.background": "#C6FF00",
    "pickerGroup.foreground": "#C6FF00",
    "tab.activeBorder": "#C6FF00",
    "notificationLink.foreground": "#C6FF00"
  },
  "explorer.confirmDragAndDrop": false,
  "typescript.updateImportsOnFileMove.enabled": "always",
  "breadcrumbs.enabled": true,
  "vim.disableExtension": false,
  "gitlens.views.fileHistory.enabled": true,
  "gitlens.views.lineHistory.enabled": true,
  "javascript.implicitProjectConfig.experimentalDecorators": true,
  "javascript.updateImportsOnFileMove.enabled": "always",
  "terminal.integrated.fontFamily": "Ubuntu Mono derivative Powerline",
  "terminal.integrated.shell.windows": "C:\\Windows\\Sysnative\\bash.exe"
}
```

## Ubuntu Mono

- https://design.ubuntu.com/font/

## Ubuntu Mono derivative Powerline

- https://github.com/powerline/fonts/tree/master/UbuntuMono

## in-terminal with Bash On Ubuntu

- Windows `Bash on Ubuntu` 를 활용한 vscode 내 터미널을 사용하기 위해서는 윈도우 스토어에서 `Ubuntu` 가 설치되어있어야함
  - https://www.microsoft.com/store/productId/9NBLGGH4MSV6
