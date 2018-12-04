import path from "path";

import defaultWebpackConfig from "@phenomic/plugin-bundler-webpack/lib/webpack.config.js";
/*
import { BundleAnalyzerPlugin } from "webpack-bundle-analyzer";
*/

module.exports = (config /*: PhenomicConfig*/) => {
  const webpackConfig = defaultWebpackConfig(config);
  return Object.assign({}, webpackConfig, {
    module: {
      rules: [
        // https://github.com/apollographql/apollo-link-state/issues/302
        // https://github.com/graphql/graphql-js/issues/1272#issuecomment-393903706
        {
          test: /\.mjs$/,
          include: /node_modules/,
          type: "javascript/auto"
        }
      ].concat(webpackConfig.module.rules)
    },
    resolve: Object.assign({}, webpackConfig.resolve, {
      alias: {
        "react-native$": "react-native-web"
      }
    })
    /*
    plugins: [
      new BundleAnalyzerPlugin({
        analyzerMode: "static"
      })
    ].concat(webpackConfig.plugins)
    */
  });
};
