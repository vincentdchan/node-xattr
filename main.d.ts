
// sync function

export function getXattrSync(path: string, name: string): Buffer;
export function getXattrSync(path: string, name: string, encoding: string): string;

export function setXattrSync(path: string, name: string, value: string | Buffer): void;

export function listXattrSync(path: string): string[];

export function removeXattrSync(path: string, name: string): void;

// promise function

export function getXattr(path: string, name: string): Promise<Buffer>;
export function getXattr(path: string, name: string, encoding: string): Promise<string>;

export function setXattr(path: string, name: string, value: string | Buffer): Promise<void>;

export function listXattr(path: string): Promise<string[]>;

export function removeXattr(path: string, name: string): Promise<void>;

namespace macUtils {
  export function setCustomIcon(filePath: string, iconPath: string): Promise<void>;
  export function setCustomIconSync(filePath: string, iconPath: string): void;

  export function serializeArrayOfString(content: string[]): Buffer;
  export function deserializeArrayOfString(buffer: Buffer): string[];

}
