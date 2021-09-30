<GameFile>
  <PropertyGroup Name="UIMainScene" Type="Scene" ID="a2ee0952-26b5-49ae-8bf9-4f1d6279b798" Version="3.10.0.0" />
  <Content ctype="GameProjectContent">
    <Content>
      <Animation Duration="0" Speed="1.0000" />
      <ObjectData Name="Scene" ctype="GameNodeObjectData">
        <Size X="960.0000" Y="640.0000" />
        <Children>
          <AbstractNodeData Name="Default" ActionTag="953446860" Tag="5" IconVisible="False" ctype="SpriteObjectData">
            <Size X="960.0000" Y="640.0000" />
            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
            <Position X="480.0000" Y="320.0000" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition X="0.5000" Y="0.5000" />
            <PreSize X="1.0000" Y="1.0000" />
            <FileData Type="Normal" Path="HelloWorld.png" Plist="" />
            <BlendFunc Src="1" Dst="771" />
          </AbstractNodeData>
          <AbstractNodeData Name="Panel_1" ActionTag="-1347599646" Tag="5" IconVisible="False" LeftMargin="148.9998" RightMargin="311.0002" TopMargin="32.0000" BottomMargin="578.0000" TouchEnable="True" ClipAble="False" BackColorAlpha="102" ComboBoxIndex="1" ColorAngle="90.0000" Scale9Width="1" Scale9Height="1" ctype="PanelObjectData">
            <Size X="500.0000" Y="30.0000" />
            <Children>
              <AbstractNodeData Name="TextField_1" ActionTag="-1777382623" Tag="10" IconVisible="False" LeftMargin="10.0000" RightMargin="90.0000" TopMargin="5.2200" BottomMargin="4.7800" TouchEnable="True" FontSize="20" IsCustomSize="True" LabelText="" PlaceHolderText="Text Field" MaxLengthText="10" ctype="TextFieldObjectData">
                <Size X="400.0000" Y="20.0000" />
                <AnchorPoint ScaleY="0.5000" />
                <Position X="10.0000" Y="14.7800" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition X="0.0200" Y="0.4927" />
                <PreSize X="0.8000" Y="0.6667" />
              </AbstractNodeData>
              <AbstractNodeData Name="Button_1" ActionTag="-1294719246" CallBackType="Click" CallBackName="onMsgHandler" Tag="6" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="425.0000" RightMargin="5.0000" TopMargin="-3.0000" BottomMargin="-3.0000" TouchEnable="True" FontSize="14" ButtonText="发送" Scale9Enable="True" LeftEage="15" RightEage="15" TopEage="11" BottomEage="11" Scale9OriginX="15" Scale9OriginY="11" Scale9Width="16" Scale9Height="14" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="ButtonObjectData">
                <Size X="70.0000" Y="36.0000" />
                <AnchorPoint ScaleX="1.0000" ScaleY="0.5000" />
                <Position X="495.0000" Y="15.0000" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition X="0.9900" Y="0.5000" />
                <PreSize X="0.1400" Y="1.2000" />
                <TextColor A="255" R="65" G="65" B="70" />
                <DisabledFileData Type="Default" Path="Default/Button_Disable.png" Plist="" />
                <PressedFileData Type="Default" Path="Default/Button_Press.png" Plist="" />
                <NormalFileData Type="Default" Path="Default/Button_Normal.png" Plist="" />
                <OutlineColor A="255" R="255" G="0" B="0" />
                <ShadowColor A="255" R="110" G="110" B="110" />
              </AbstractNodeData>
            </Children>
            <AnchorPoint />
            <Position X="148.9998" Y="578.0000" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition X="0.1552" Y="0.9031" />
            <PreSize X="0.5208" Y="0.0469" />
            <SingleColor A="255" R="150" G="200" B="255" />
            <FirstColor A="255" R="150" G="200" B="255" />
            <EndColor A="255" R="255" G="255" B="255" />
            <ColorVector ScaleY="1.0000" />
          </AbstractNodeData>
          <AbstractNodeData Name="ListView_1" ActionTag="337099841" Tag="6" IconVisible="False" LeftMargin="138.0000" RightMargin="72.0000" TopMargin="96.0000" BottomMargin="44.0000" TouchEnable="True" ClipAble="False" BackColorAlpha="240" ComboBoxIndex="1" ColorAngle="90.0000" Scale9Width="1" Scale9Height="1" ScrollDirectionType="0" DirectionType="Vertical" ctype="ListViewObjectData">
            <Size X="750.0000" Y="500.0000" />
            <AnchorPoint />
            <Position X="138.0000" Y="44.0000" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition X="0.1437" Y="0.0688" />
            <PreSize X="0.7813" Y="0.7813" />
            <SingleColor A="255" R="150" G="150" B="255" />
            <FirstColor A="255" R="150" G="150" B="255" />
            <EndColor A="255" R="255" G="255" B="255" />
            <ColorVector ScaleY="1.0000" />
          </AbstractNodeData>
          <AbstractNodeData Name="ServerItem" ActionTag="1876865855" Tag="7" IconVisible="False" LeftMargin="138.0000" RightMargin="72.0000" TopMargin="102.0000" BottomMargin="478.0000" TouchEnable="True" ClipAble="False" BackColorAlpha="171" ComboBoxIndex="1" ColorAngle="90.0000" Scale9Width="1" Scale9Height="1" ctype="PanelObjectData">
            <Size X="750.0000" Y="60.0000" />
            <Children>
              <AbstractNodeData Name="Text_2" ActionTag="45020996" Tag="10" IconVisible="False" LeftMargin="13.0000" RightMargin="697.0000" TopMargin="20.0000" BottomMargin="20.0000" FontSize="20" LabelText="name" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
                <Size X="40.0000" Y="20.0000" />
                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                <Position X="33.0000" Y="30.0000" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition X="0.0440" Y="0.5000" />
                <PreSize X="0.0533" Y="0.3333" />
                <OutlineColor A="255" R="255" G="0" B="0" />
                <ShadowColor A="255" R="110" G="110" B="110" />
              </AbstractNodeData>
              <AbstractNodeData Name="TextField_2" ActionTag="262991843" Tag="4" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="78.5250" RightMargin="71.4750" TopMargin="18.0000" BottomMargin="12.0000" TouchEnable="True" FontSize="20" IsCustomSize="True" LabelText="" PlaceHolderText="Text Field" MaxLengthText="10" ctype="TextFieldObjectData">
                <Size X="600.0000" Y="30.0000" />
                <AnchorPoint ScaleY="0.5000" />
                <Position X="78.5250" Y="27.0000" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition X="0.1047" Y="0.4500" />
                <PreSize X="0.8000" Y="0.5000" />
              </AbstractNodeData>
              <AbstractNodeData Name="Button_2" ActionTag="1077283501" CallBackType="Click" CallBackName="onMsgHandler" Tag="8" IconVisible="False" LeftMargin="696.0000" RightMargin="8.0000" TopMargin="15.0000" BottomMargin="9.0000" TouchEnable="True" FontSize="14" ButtonText="发送" Scale9Enable="True" LeftEage="15" RightEage="15" TopEage="11" BottomEage="11" Scale9OriginX="15" Scale9OriginY="11" Scale9Width="16" Scale9Height="14" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="ButtonObjectData">
                <Size X="46.0000" Y="36.0000" />
                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                <Position X="719.0000" Y="27.0000" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition X="0.9587" Y="0.4500" />
                <PreSize X="0.0613" Y="0.6000" />
                <TextColor A="255" R="65" G="65" B="70" />
                <DisabledFileData Type="Default" Path="Default/Button_Disable.png" Plist="" />
                <PressedFileData Type="Default" Path="Default/Button_Press.png" Plist="" />
                <NormalFileData Type="Default" Path="Default/Button_Normal.png" Plist="" />
                <OutlineColor A="255" R="255" G="0" B="0" />
                <ShadowColor A="255" R="110" G="110" B="110" />
              </AbstractNodeData>
            </Children>
            <AnchorPoint />
            <Position X="138.0000" Y="478.0000" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition X="0.1437" Y="0.7469" />
            <PreSize X="0.7813" Y="0.0938" />
            <SingleColor A="255" R="150" G="200" B="255" />
            <FirstColor A="255" R="150" G="200" B="255" />
            <EndColor A="255" R="255" G="255" B="255" />
            <ColorVector ScaleY="1.0000" />
          </AbstractNodeData>
        </Children>
      </ObjectData>
    </Content>
  </Content>
</GameFile>