object Parameters: TParameters
  Left = 473
  Top = 224
  BorderStyle = bsDialog
  Caption = 'Parameters'
  ClientHeight = 214
  ClientWidth = 545
  Color = clBtnFace
  ParentFont = True
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
  OldCreateOrder = True
  Position = poScreenCenter
  PixelsPerInch = 96
  TextHeight = 13
  object Bevel1: TBevel
    Left = 8
    Top = 8
    Width = 529
    Height = 161
    Shape = bsFrame
  end
  object OKBtn: TButton
    Left = 351
    Top = 180
    Width = 90
    Height = 25
    Caption = 'OK'
    Default = True
    ModalResult = 1
    TabOrder = 0
    OnClick = OKBtnClick
  end
  object CancelBtn: TButton
    Left = 448
    Top = 180
    Width = 90
    Height = 25
    Cancel = True
    Caption = 'Cancel'
    ModalResult = 2
    TabOrder = 1
  end
  object CmdLine: TLabeledEdit
    Left = 16
    Top = 32
    Width = 401
    Height = 24
    EditLabel.Width = 90
    EditLabel.Height = 16
    EditLabel.Caption = 'Command Line'
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
  object Browse1: TButton
    Left = 432
    Top = 32
    Width = 97
    Height = 25
    Caption = 'Browse 4 file...'
    TabOrder = 3
    OnClick = Browse1Click
  end
  object WorkDir: TLabeledEdit
    Left = 16
    Top = 112
    Width = 401
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
    TabOrder = 4
  end
  object Browse2: TButton
    Left = 432
    Top = 112
    Width = 97
    Height = 25
    Caption = 'Browse...'
    TabOrder = 5
    OnClick = Browse2Click
  end
  object OpenDialog: TOpenDialog
    FileName = 
      'C:\Program Files\Borland\CBuilder6\Projects\Cracker\fParameters.' +
      '~dfm'
    Filter = 'Any File (*.*)|*.*'
    Left = 264
    Top = 112
  end
end
