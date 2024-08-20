# What is react-native-phi3?

`react-native-phi3` is a C++ wrapper of [Phi3](https://huggingface.co/microsoft/Phi-3-mini-4k-instruct-onnx) model for [onnxruntime](https://github.com/microsoft/onnxruntime) which runs on both android and IOS.

## Installation

```sh
npm install react-native-phi3
```

## Usage

```js
import { useEffect, useState } from 'react';
import { Text, View, Button } from 'react-native';
import { init, ask } from 'react-native-phi3';

/**
 * The directory which contains onnx model, simply download this folder into user's device
 * or creating your own custom phi3 onnx model: 
 * https://huggingface.co/microsoft/Phi-3-mini-4k-instruct-onnx/tree/main/cpu_and_mobile/cpu-int4-rtn-block-32
 * */
const MODEL_DIRECTORY = "path/to/your/phi3-onnx/"

const App = () {
    
    const [mLoaded, setMLoaded] = useState(false)
    useEffect(() => {
        init(MODEL_DIRECTORY).then(success => {
            console.info(`loading phi3 model ${success}`)
            setMLoaded(success)
        }).catch((error) => {
            console.info(`Error happening when loading phi3 model`)
            setMLoaded(false)
        })
    })

    return (
        <View>
            <Text>Your model is loaded: {mLoaded}</Text>
            <Button title={"Ask"} onPress={ async () => { 
                const results = await ask("Can you tell me a joke");
                console.info(results);
                }}/>
        </View>
    )
}

```

A full setup to download assets and running inference is available [here](https://github.com/Vibrat/react-native-phi3/tree/main/example)

## Contributing

See the [contributing guide](CONTRIBUTING.md) to learn how to contribute to the repository and the development workflow.

## License

MIT

---

Made with [create-react-native-library](https://github.com/callstack/react-native-builder-bob)
