object Parameters: TParameters
  Left = 446
  Top = 277
  BorderStyle = bsToolWindow
  Caption = 'Parameters'
  ClientHeight = 206
  ClientWidth = 632
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  FormStyle = fsStayOnTop
  Icon.Data = {
    0000010001002020000000000000E80200001600000028000000200000004000
    0000010004000000000000020000000000000000000000000000000000000000
    0000800000000080000080800000000080008000800000808000C0C0C0008080
    8000FF00000000FF0000FFFF00000000FF00FF00FF0000FFFF00FFFFFF000000
    0000000000000000000000000000000000000000000000000000000000000000
    0000000000000000000000000000000000000000000000000000000000000000
    0000000000008999EE899910000000000000000000008999EE89B91000000000
    0000000000007999EE89B9100000000000000000000079998889991000000000
    000099998E8979999999991000000000000089998E89B9999999991000009999
    9999B9998E89B99999999910000099999999B9998889B96699669910000098EE
    9988B9999999B9EE99EE9911111099EE9988B9999999B988998899113310998E
    9988B9999999B99999999911331099889988B9EE9988B9669966991133109999
    9999B9EE9988B9EE99EE9916E81099999999B97E9988B988998899188310998E
    9988B9889988B99999999911331099889988B9999999B9669966991133109999
    9999B9999999B9EE99EE9916E81099999999B9999999B977997799188910998E
    9988B9999999B99999999911991099889988B9EE9988BBBBBBBBBBB199109999
    9999B97E9988910000119818E81000000000B97E998E91000099889888100000
    0000B9779988910000999999991000000000B999999991000099999999900000
    0000B9999999910000000000000000000000BBBBBBBBBB000000000000000000
    000000000000000000000000000000000000000000000000000000000000FFFF
    FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF001FFFFF001FFFFF001FFFFF001FFF00
    001FFF00001F0000001F0000001F000000010000000100000001000000010000
    0001000000010000000100000001000000010000000100000001000000010000
    3C01FF003C01FF003C01FF003C01FF003FFFFF003FFFFFFFFFFFFFFFFFFF}
  OldCreateOrder = False
  OnKeyUp = FormKeyUp
  PixelsPerInch = 96
  TextHeight = 13
  object CmdLine: TLabeledEdit
    Left = 8
    Top = 24
    Width = 497
    Height = 24
    EditLabel.Width = 96
    EditLabel.Height = 16
    EditLabel.Caption = 'Command Line :'
    EditLabel.Font.Charset = DEFAULT_CHARSET
    EditLabel.Font.Color = clWindowText
    EditLabel.Font.Height = -13
    EditLabel.Font.Name = 'MS Sans Serif'
    EditLabel.Font.Style = []
    EditLabel.ParentFont = False
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    LabelPosition = lpAbove
    LabelSpacing = 3
    ParentFont = False
    TabOrder = 0
  end
  object Browse1: TButton
    Left = 520
    Top = 24
    Width = 105
    Height = 25
    Caption = 'Browse for file...'
    TabOrder = 1
    OnClick = Browse1Click
  end
  object WorkDir: TLabeledEdit
    Left = 8
    Top = 96
    Width = 497
    Height = 24
    EditLabel.Width = 107
    EditLabel.Height = 16
    EditLabel.Caption = 'Working Directory'
    EditLabel.Font.Charset = DEFAULT_CHARSET
    EditLabel.Font.Color = clWindowText
    EditLabel.Font.Height = -13
    EditLabel.Font.Name = 'MS Sans Serif'
    EditLabel.Font.Style = []
    EditLabel.ParentFont = False
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    LabelPosition = lpAbove
    LabelSpacing = 3
    ParentFont = False
    TabOrder = 2
  end
  object Browse2: TButton
    Left = 520
    Top = 96
    Width = 105
    Height = 25
    Caption = 'Browse...'
    TabOrder = 3
    OnClick = Browse2Click
  end
  object OK: TButton
    Left = 520
    Top = 168
    Width = 105
    Height = 25
    Caption = 'OK'
    Default = True
    TabOrder = 4
    OnClick = OKClick
  end
  object Cancel: TButton
    Left = 392
    Top = 168
    Width = 97
    Height = 25
    Caption = 'Cancel'
    ModalResult = 2
    TabOrder = 5
    OnClick = CancelClick
  end
  object OpenDialog: TOpenDialog
    Filter = 'Any File (*.*)|*.*'
    Options = [ofHideReadOnly, ofNoValidate, ofCreatePrompt, ofEnableSizing, ofForceShowHidden]
    Title = 'Select a file'
    Left = 32
    Top = 136
  end
end
