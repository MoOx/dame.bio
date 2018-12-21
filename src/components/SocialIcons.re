open BsReactNative;

let styles =
  StyleSheet.create(Style.{"iconWrapper": style([flexGrow(1.)])});

let component = ReasonReact.statelessComponent("SocialIcons");

let make =
    (
      ~wrapperStyle,
      ~iconStyle,
      ~iconColor="#fff",
      ~iconSize=16.,
      /* note the default value that just wrap with a simple node */
      ~iconWrapperFunc=(~children) => <Text> ...children </Text>,
      _children,
    ) => {
  ...component,
  render: _self =>
    <View style=wrapperStyle>
      <TouchableOpacityLink
        style=styles##iconWrapper href="https://www.instagram.com/dame.bio/">
        <Text style=iconStyle>
          {iconWrapperFunc(
             ~children=[|
               <Text>
                 <SVGSocialInstagram
                   fill=iconColor
                   width=iconSize
                   height=iconSize
                 />
               </Text>,
             |],
           )}
        </Text>
      </TouchableOpacityLink>
      <TouchableOpacityLink
        style=styles##iconWrapper href="https://www.pinterest.com/damebio/">
        <Text style=iconStyle>
          {iconWrapperFunc(
             ~children=[|
               <Text>
                 <SVGSocialPinterest
                   fill=iconColor
                   width=iconSize
                   height=iconSize
                 />
               </Text>,
             |],
           )}
        </Text>
      </TouchableOpacityLink>
      <TouchableOpacityLink
        style=styles##iconWrapper href="https://twitter.com/damebio/">
        <Text style=iconStyle>
          {iconWrapperFunc(
             ~children=[|
               <Text>
                 <SVGSocialTwitter
                   fill=iconColor
                   width=iconSize
                   height=iconSize
                 />
               </Text>,
             |],
           )}
        </Text>
      </TouchableOpacityLink>
      <TouchableOpacityLink
        style=styles##iconWrapper href="https://www.facebook.com/Damebio/">
        <Text style=iconStyle>
          {iconWrapperFunc(
             ~children=[|
               <Text>
                 <SVGSocialFacebook
                   fill=iconColor
                   width=iconSize
                   height=iconSize
                 />
               </Text>,
             |],
           )}
        </Text>
      </TouchableOpacityLink>
    </View>,
  /* <TouchableOpacityLink style=styles##iconWrapper href="#">
       <Text style=iconStyle>
         {iconWrapperFunc(
            ~children=[|
              <Text>
                <SVGSocialYoutube
                  fill=iconColor
                  width=iconSize
                  height=iconSize
                />
              </Text>,
            |],
          )}
       </Text>
     </TouchableOpacityLink>
     <TouchableOpacityLink style=styles##iconWrapper href="#">
       <Text style=iconStyle>
         {iconWrapperFunc(
            ~children=[|
              <Text>
                <SVGRssFeed fill=iconColor width=iconSize height=iconSize />
              </Text>,
            |],
          )}
       </Text>
     </TouchableOpacityLink> */
};
