
// sync function

export function getXattrSync(path: string, name: string): Buffer;
export function getXattrSync(path: string, name: string, encoding: string): string;

export function setXattrSync(path: string, name: string, value: string | Buffer): void;

export function listXattrSync(path: string): string[];

export function removeXattrSync(path: string, name: string): void;

// async function

export function getXattr(path: string, name: string, callaback: (err?: Error, buffer: Buffer) => void): void;
export function getXattr(path: string, name: string, encoding: string, callaback: (err?: Error, value: string) => void): void;

export function setXattr(path: string, name: string, value: string | Buffer, callback: (err?: Error) => void);

export function listXattr(path: string, callback: (err?: Error, list: string[]) => void);

export function removeXattr(path: string, name: string, callback: (err?: Error) => void);
