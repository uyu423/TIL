# 요우의 Visual Studio Code Setting JSON

- [VsCode/초기 세팅.md](https://github.com/uyu423/TIL/blob/master/VsCode/%EC%B4%88%EA%B8%B0%20%EC%84%B8%ED%8C%85.md) 가 선행되어야하는 설정들이 포함되어 있습니다.
- ~~나는 모르겠는데 쓰다보니 자꾸 이상한 옵션이 막 생긴다~~

```json
  "workbench.iconTheme": "vscode-icons",
  "editor.fontFamily": "Ubuntu Mono",
  "editor.autoIndent": true,
  "editor.tabSize": 2,
  "editor.fontSize": 20,
  "editor.wordWrap": "on",
  "tslint.autoFixOnSave": true,
  "eslint.validate":  [
    "javascript",
    "javascriptreact",
    {"language":  "typescript",  "autoFix":  true  },
    {"language":  "typescriptreact",  "autoFix":  true  }
  ],
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
  "terminal.integrated.fontFamily": "Ubuntu Mono derivative Powerline"
```

## Ubuntu Mono

- https://design.ubuntu.com/font/

## Ubuntu Mono derivative Powerline

- https://github.com/powerline/fonts/tree/master/UbuntuMono
