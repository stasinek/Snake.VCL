object OpcjeForm: TOpcjeForm
  Left = 426
  Top = 419
  Anchors = [akLeft]
  BorderStyle = bsDialog
  Caption = 'Snake: OPCJE'
  ClientHeight = 231
  ClientWidth = 639
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = True
  Position = poScreenCenter
  PrintScale = poNone
  PixelsPerInch = 96
  TextHeight = 13
  object TabControl1: TTabControl
    Left = 0
    Top = 0
    Width = 639
    Height = 231
    Align = alClient
    MultiLine = True
    Style = tsFlatButtons
    TabHeight = 40
    TabOrder = 4
    Tabs.Strings = (
      'COUNT'
      'REF TIME'
      'EXTRA COUNT')
    TabIndex = 0
    object Bevel1: TBevel
      Left = 4
      Top = 156
      Width = 631
      Height = 71
      Align = alBottom
      Constraints.MinHeight = 70
      Constraints.MinWidth = 630
    end
    object Bevel2: TBevel
      Left = 4
      Top = 46
      Width = 631
      Height = 110
      Align = alClient
    end
    object UpDown2: TUpDown
      Left = 330
      Top = 68
      Width = 87
      Height = 65
      Anchors = [akTop, akRight]
      Min = 0
      Position = 0
      TabOrder = 0
      Wrap = False
    end
    object Edit2: TEdit
      Left = 422
      Top = 68
      Width = 105
      Height = 66
      Anchors = [akTop, akRight]
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -48
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
      TabOrder = 1
      Text = '0'
    end
  end
  object BitBtn1: TBitBtn
    Left = 520
    Top = 168
    Width = 103
    Height = 48
    Anchors = [akRight]
    Caption = 'OK'
    TabOrder = 0
    OnClick = BitBtn1Click
  end
  object Edit1: TEdit
    Left = 30
    Top = 68
    Width = 105
    Height = 66
    Anchors = [akTop, akRight]
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -48
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
    TabOrder = 1
    Text = '0'
  end
  object BitBtn2: TBitBtn
    Left = 405
    Top = 168
    Width = 100
    Height = 48
    Anchors = [akRight]
    Caption = 'Cancel'
    TabOrder = 2
    OnClick = BitBtn2Click
  end
  object UpDown1: TUpDown
    Left = 534
    Top = 68
    Width = 87
    Height = 65
    Anchors = [akTop, akRight]
    Min = 0
    Position = 0
    TabOrder = 3
    Wrap = False
  end
  object UpDown3: TUpDown
    Left = 130
    Top = 68
    Width = 87
    Height = 65
    Anchors = [akTop, akRight]
    Min = 0
    Position = 0
    TabOrder = 5
    Wrap = False
  end
  object Edit3: TEdit
    Left = 222
    Top = 68
    Width = 105
    Height = 66
    Anchors = [akTop, akRight]
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -48
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
    TabOrder = 6
    Text = '0'
  end
end
