// @flow

import defaultWebpackConfig from "@phenomic/plugin-bundler-webpack/lib/webpack.config.js";
// import { BundleAnalyzerPlugin } from "webpack-bundle-analyzer";

module.exports = (config /*: PhenomicConfig*/) => {
  const webpackConfig = defaultWebpackConfig(config);
  return {
    ...webpackConfig,
    module: {
      ...webpackConfig.module,
      rules: [
        // ...webpackConfig.module.rules,
        // reuse phenomic default babel loader and add react-native(-web) alias
        // to our code
        {
          ...webpackConfig.module.rules[0],
          use: [
            {
              ...webpackConfig.module.rules[0].use[0],
              options: {
                ...webpackConfig.module.rules[0].use[0].options,
                plugins: [
                  [
                    "babel-plugin-module-resolver",
                    { alias: { "^react-native$": "react-native-web" } }
                  ]
                ]
              }
            }
          ]
        },
        // reuse phenomic default babel loader and add react-native(-web) alias
        // to node_modules using react-native
        {
          ...webpackConfig.module.rules[0],
          exclude: undefined,
          include: [/node_modules\/bs-react-native\/lib/],
          use: [
            {
              ...webpackConfig.module.rules[0].use[0],
              options: {
                plugins: [
                  [
                    "babel-plugin-module-resolver",
                    { alias: { "^react-native$": "react-native-web" } }
                  ]
                ]
              }
            }
          ]
        },
        webpackConfig.module.rules[1],
        // https://github.com/apollographql/apollo-link-state/issues/302
        // https://github.com/graphql/graphql-js/issues/1272#issuecomment-393903706
        { test: /\.mjs$/, include: /node_modules/, type: "javascript/auto" }
      ]
    }
  };
  // plugins: [
  //   ...webpackConfig.plugins,
  //   new BundleAnalyzerPlugin({
  //     analyzerMode: "static"
  //   })
  // ]
};
