open BsReactNative;

let component = ReasonReact.statelessComponent("SocialIcons");

let make =
    (
      ~wrapperStyle,
      ~iconStyle,
      ~iconColor="#fff",
      ~iconSize=16.,
      /* note the default value that just wrap with a simple node */
      ~iconWrapperFunc=(~children) => <Text> ...children </Text>,
      _children
    ) => {
  ...component,
  render: _self =>
    <View style=wrapperStyle>
      <TextLink style=iconStyle href="https://www.facebook.com/Damebio/">
        (
          iconWrapperFunc(
            ~children=[|
              <SVGSocialFacebook
                fill=iconColor
                width=iconSize
                height=iconSize
              />
            |]
          )
        )
      </TextLink>
      <TextLink style=iconStyle href="https://twitter.com/damebio/">
        (
          iconWrapperFunc(
            ~children=[|
              <SVGSocialTwitter
                fill=iconColor
                width=iconSize
                height=iconSize
              />
            |]
          )
        )
      </TextLink>
      <TextLink style=iconStyle href="https://www.instagram.com/dame.bio/">
        (
          iconWrapperFunc(
            ~children=[|
              <SVGSocialInstagram
                fill=iconColor
                width=iconSize
                height=iconSize
              />
            |]
          )
        )
      </TextLink>
      <TextLink
        style=iconStyle href="https://fr.pinterest.com/source/dame.bio/">
        (
          iconWrapperFunc(
            ~children=[|
              <SVGSocialPinterest
                fill=iconColor
                width=iconSize
                height=iconSize
              />
            |]
          )
        )
      </TextLink>
      <TextLink style=iconStyle href="http://www.hellocoton.fr/mapage/liloue">
        (
          iconWrapperFunc(
            ~children=[|
              <SVGSocialHelloCoton
                fill=iconColor
                width=iconSize
                height=iconSize
              />
            |]
          )
        )
      </TextLink>
      <TextLink style=iconStyle href="#">
        (
          iconWrapperFunc(
            ~children=[|
              <SVGSocialYoutube
                fill=iconColor
                width=iconSize
                height=iconSize
              />
            |]
          )
        )
      </TextLink>
      <TextLink style=iconStyle href="#">
        (
          iconWrapperFunc(
            ~children=[|
              <SVGRssFeed fill=iconColor width=iconSize height=iconSize />
            |]
          )
        )
      </TextLink>
    </View>
};
