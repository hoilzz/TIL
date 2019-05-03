The "d.ts" file is used to provide typescript type information about an API that's written in JavaScript. The idea is that you're using something like jQuery or underscore, an existing javascript library. You want to consume those from your typescript code.

Rather than rewriting jquery or underscore or whatever in typescript, you can instead write the d.ts file, which contains only the type annotations. Then from your typescript code you get the typescript benefits of static type checking while still using a pure JS library.

## declaration files

When a TypeScript script gets compiled there is an option to generate a declaration file (with the extension .d.ts) that functions as an interface to the components in the compiled JavaScript. In the process the compiler strips away all function and method bodies and preserves only the signatures of the types that are exported. The resulting declaration file can then be used to describe the exported virtual TypeScript types of a JavaScript library or module when a third-party developer consumes it from TypeScript.

The concept of declaration files is analogous to the concept of header file found in C/C++.

```ts
declare module arithmetics {
    add(left: number, right: number): number;
    subtract(left: number, right: number): number;
    multiply(left: number, right: number): number;
    divide(left: number, right: number): number;
}
```

Type declaration files can be written by hand for existing JavaScript libraries, as has been done for jQuery and Node.js.

Large collections of declaration files for popular JavaScript libraries are hosted on GitHub in DefinitelyTyped and the Typings Registry. A command-line utility called typings is provided to help search and install declaration files from the repositories.
