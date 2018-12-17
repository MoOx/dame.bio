open BsReactNative;

let component = ReasonReact.statelessComponent("HeaderTopbar");

let styles =
  StyleSheet.create(
    Style.{
      "topbarWrapper": style([backgroundColor(String("#006579"))]),
      "icons": style([flexDirection(Row)]),
      "topbarLinks": style([flexDirection(Row)]),
      "topbarLink":
        style([
          paddingVertical(Pt(6.)),
          paddingHorizontal(Pt(12.)),
          fontSize(Float(12.)),
          color(String("#fff")),
        ]),
    },
  );

let make = _children => {
  ...component,
  render: _self =>
    <ContainerWithSpace wrapperStyle=styles##topbarWrapper>
      <SocialIcons wrapperStyle=styles##icons iconStyle=styles##topbarLink />
      <View
        style=styles##topbarLinks
        /*
         <TextLink style=styles##topbarLink href="/a-propos">
           {ReasonReact.string({j|À Propos|j})}
         </TextLink>
         <TextLink style=styles##topbarLink href="/univers">
           {ReasonReact.string({j|Univers du site|j})}
         </TextLink>
         <TextLink style=styles##topbarLink href="/colibri">
           {ReasonReact.string({j|Un colibri en action|j})}
         </TextLink>
         <TextLink style=styles##topbarLink href="/contact">
           {ReasonReact.string({j|Contact|j})}
         </TextLink>
         */
      />
    </ContainerWithSpace>,
};
