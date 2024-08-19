import { NativeModules, Platform } from 'react-native';

const LINKING_ERROR =
  `The package 'react-native-phi3' doesn't seem to be linked. Make sure: \n\n` +
  Platform.select({ ios: "- You have run 'pod install'\n", default: '' }) +
  '- You rebuilt the app after installing the package\n' +
  '- You are not using Expo Go\n';

const EnglePhi3 = NativeModules.EnglePhi3
  ? NativeModules.EnglePhi3
  : new Proxy(
      {},
      {
        get() {
          throw new Error(LINKING_ERROR);
        },
      }
    );

export function ask(text: string): Promise<string> {
  return EnglePhi3.ask(text);
}

export function init(path: string): Promise<boolean> {
  return EnglePhi3.init(path);
}
