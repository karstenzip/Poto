export default function compareArrayBuffer(
	buffer1: ArrayBuffer,
	buffer2: ArrayBuffer
): boolean {
	if (buffer1.byteLength !== buffer2.byteLength) return false
	const array1 = new Uint8Array(buffer1)
	const array2 = new Uint8Array(buffer2)
	for (let i = 0; i < array1.length; i++) {
		if (array1[i] !== array2[i]) return false
	}
	return true
}
